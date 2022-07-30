#include "t_program_editor.h"
#include "t_performance_monitor.h"
#include "t_globals.h"
#include "t_config.h"
#include "t_compiler.h"
#include "t_interpreter.h"
#include "t_machine.h"
#include "chars.h"
#include "t_panel.h"
#include "t_input_widget.h"
#include "t_alert_widget.h"

#define PTM_EDITOR_WINDOW_TITLE		"PTM"

t_program_editor::t_program_editor(t_globals* g) : t_ui_base(g) {
	perfmon = g->perfmon;
	wnd->SetTitle(PTM_EDITOR_WINDOW_TITLE);
	csr_overwrite = false;
	prg_view.max_chars = wnd->Cols - 2;
	prg_view.max_lines = wnd->Rows - 2;
	info_visible = true;
	snd = g->snd;

	draw_everything();

	if (!g->cfg->autorun.empty()) {
		if (File::Exists(g->cfg->autorun)) {
			load_program(g->cfg->autorun);
			compile_and_run();
		}
	} else if (!g->cfg->autoload.empty()) {
		load_program(g->cfg->autoload);
	} else {
		unsaved = false;
	}
	if (prg.src_lines.empty()) {
		add_empty_line();
	}
}
t_program_editor::~t_program_editor() {
}
void t_program_editor::on_run_loop() { // This method needs to be fast!
	if (wnd && perfmon) wnd->SetTitle(perfmon->format_info());
	draw_only_whats_needed();
}
bool t_program_editor::on_exit() {
	if (unsaved) {
		const auto result = confirm("There are unsaved changes. Save? (Y/N)");
		if (result == t_confirm_result::yes) save_program(prg_filename);
		else if (result == t_confirm_result::cancel) return false;
	}
	return true;
}
void t_program_editor::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (!shift && !ctrl && key != SDLK_DELETE) {
		cancel_line_selection();
	}
	if (TKey::Alt() && key == SDLK_RETURN) {
		wnd->ToggleFullscreen();
	} else if (ctrl && key == SDLK_q) {
		if (on_exit()) running = false;
	} else if (key == SDLK_F1) {
		show_help();
	} else if (key == SDLK_ESCAPE) {
		cancel_line_selection();
	} else if (key == SDLK_RIGHT) {
		move_prg_csr_right();
	} else if (key == SDLK_LEFT) {
		move_prg_csr_left();
	} else if (key == SDLK_DOWN) {
		if (shift && !has_selection()) line_selection_start = prg_csr.line_ix;
		move_prg_csr_down();
	} else if (key == SDLK_UP) {
		if (shift && !has_selection()) line_selection_start = prg_csr.line_ix;
		move_prg_csr_up();
	} else if (key == SDLK_END) {
		if (ctrl) move_prg_csr_end();
		else move_prg_csr_end_x();
	} else if (key == SDLK_HOME) {
		if (ctrl) move_prg_csr_home();
		else move_prg_csr_home_x();
	} else if (key == SDLK_PAGEUP) {
		type_pgup();
	} else if (key == SDLK_PAGEDOWN) {
		type_pgdn();
	} else if (key == SDLK_INSERT) {
		csr_overwrite = !csr_overwrite;
	} else if (key == SDLK_RETURN) {
		type_crlf();
		unsaved = true;
	} else if (key == SDLK_BACKSPACE) {
		type_backspace();
		unsaved = true;
	} else if (key == SDLK_DELETE) {
		if (has_selection()) delete_lines();
		else type_delete();
		unsaved = true;
	} else if (ctrl && key == SDLK_i) {
		info_visible = !info_visible;
	} else if (key == SDLK_F5) {
		compile_and_run();
	} else if (ctrl && key == SDLK_c) {
		copy_lines(true);
	} else if (ctrl && key == SDLK_x) {
		cut_lines();
		unsaved = true;
	} else if (ctrl && key == SDLK_v) {
		paste_lines();
		unsaved = true;
	} else if (ctrl && key == SDLK_l) {
		load_program();
	} else if (ctrl && key == SDLK_s) {
		if (shift) save_program_as();
		else save_program(prg_filename);
	} else if (ctrl && key == SDLK_n) {
		new_program();
	} else if (ctrl && key == SDLK_r) {
		reload_program();
	} else if (shift && key == SDLK_a) {
		select_entire_program();
	} else if (!ctrl && is_valid_prg_char(key)) {
		type_char(key);
		unsaved = true;
	}
}
void t_program_editor::on_mouse_wheel(int dist_y) {
	for (int i = 0; i < abs(dist_y) * 3; i++) {
		if (dist_y > 0) {
			move_prg_csr_down();
		} else if (dist_y < 0) {
			move_prg_csr_up();
		}
	}
}
void t_program_editor::draw_everything() {
	draw_screen_base();
	draw_border_info();
	draw_program();
	apply_syntax_coloring();
	draw_cursor();
}
void t_program_editor::draw_only_whats_needed() {
	//draw_cursor();
	draw_everything();
}
void t_program_editor::draw_border_info() {
	if (!info_visible) return;
	print_border_top(prg_filename, 0);
	print_border_bottom(String::Format("L:%i/%i C:%i", 
		prg_csr.line_ix + 1, prg.src_lines.size(), prg_csr.char_ix), 0);
	if (unsaved) {
		print_border_bottom("Unsaved", 36);
	}
}
void t_program_editor::draw_program() {
	int x = 1;
	int y = 1;
	for (int line_ix = prg_view.first_line_ix; line_ix < prg_view.first_line_ix + prg_view.max_lines && line_ix < prg.src_lines.size(); line_ix++) {
		x = 1;
		auto& line = prg.src_lines[line_ix];
		for (int char_ix = prg_view.first_char_ix; char_ix < prg_view.first_char_ix + prg_view.max_chars && char_ix < line.length(); char_ix++) {
			TTileSeq tile(line[char_ix], color.fg, is_selected(line_ix) ? color.sel_bg : color.bg);
			buf->SetTile(tile, prg_view.layer, x, y, false);
			if (++x > buf->LastCol - 1) break;
		}
		y++;
	}
}
void t_program_editor::apply_syntax_coloring() {
	int line_ix = prg_view.first_line_ix;
	int char_ix = prg_view.first_char_ix;
	int fgc = color.fg;
	for (int y = 1; y < buf->LastRow; y++) {
		for (int x = 1; x < buf->LastCol; x++) {
			auto& tile = buf->GetTile(0, x, y);
			if (!tile.IsEmpty()) {
				const string& line = prg.src_lines[line_ix];
				if (String::StartsWith(line, ';')) {
					fgc = color.comment_fg;
				} else if (String::StartsWith(line, ':')) {
					fgc = color.label_fg;
				} else {
					const int cmd_end_ix = String::FindFirst(line, ' ');
					if (cmd_end_ix < 0 || (char_ix >= prg_view.first_char_ix && 
						char_ix < prg_view.first_char_ix + prg_view.max_chars &&
						cmd_end_ix >= 0 && cmd_end_ix > char_ix)) {
						fgc = color.cmd_fg;
						tile.SetChar(0, String::ToUpper(tile.GetChar(0)));
					} else {
						fgc = color.fg;
					}
				}
				tile.SetForeColor(0, fgc);
			}
			char_ix++;
		}
		line_ix++;
		if (line_ix >= prg.src_lines.size()) {
			break;
		}
		char_ix = prg_view.first_char_ix;
	}
}
void t_program_editor::draw_cursor() {
	TTileSeq tile;
	if (csr_overwrite) {
		tile.Add(chars::cursor_ovr, color.csr_fg, color.bg);
	} else {
		tile.Add(chars::cursor_ins, color.csr_fg, color.bg);
	}
	tile.Add(chars::empty, color.csr_fg, color.bg);
	buf->SetTile(tile, scr_csr.layer, scr_csr.x, scr_csr.y, true);
}
void t_program_editor::hide_cursor() {
	buf->EraseTile(scr_csr.layer, scr_csr.x, scr_csr.y);
}
string* t_program_editor::get_current_line() {
	if (prg_csr.line_ix >= 0 && prg_csr.line_ix < prg.src_lines.size()) {
		return &prg.src_lines[prg_csr.line_ix];
	}
	return nullptr;
}
string* t_program_editor::get_line_below() {
	int ix = prg_csr.line_ix + 1;
	if (ix >= 0 && ix < prg.src_lines.size()) {
		return &prg.src_lines[ix];
	}
	return nullptr;
}
int t_program_editor::get_char_under_cursor() {
	string* line = get_current_line();
	if (line) {
		if (prg_csr.char_ix >= 0 && prg_csr.char_ix < line->length()) {
			return line->at(prg_csr.char_ix);
		}
	}
	return 0;
}
void t_program_editor::move_prg_csr_right() {
	string* line = get_current_line();
	if (!line) return;
	if (prg_csr.char_ix < line->length()) {
		prg_csr.char_ix++;
		if (scr_csr.x < buf->LastCol - 1) {
			scr_csr.x++;
		} else {
			prg_view.first_char_ix++;
		}
	}
}
void t_program_editor::move_prg_csr_left() {
	string* line = get_current_line();
	if (!line) return;
	if (prg_csr.char_ix > 0) {
		if (scr_csr.x > 1) {
			prg_csr.char_ix--;
			scr_csr.x--;
		} else if (prg_view.first_char_ix > 0) {
			prg_csr.char_ix--;
			prg_view.first_char_ix--;
		}
	}
}
void t_program_editor::move_prg_csr_down() {
	string* line = get_current_line();
	if (!line) return;
	if (prg_csr.line_ix < prg.src_lines.size() - 1) {
		prg_csr.line_ix++;
		if (scr_csr.y < buf->LastRow - 1) {
			scr_csr.y++;
		} else {
			prg_view.first_line_ix++;
		}
		string* line = get_current_line();
		while (prg_csr.char_ix > line->length()) {
			move_prg_csr_left();
		}
	}
}
void t_program_editor::move_prg_csr_up() {
	if (prg_csr.line_ix > 0) {
		prg_csr.line_ix--;
		if (scr_csr.y > 1) {
			scr_csr.y--;
		} else {
			prg_view.first_line_ix--;
		}
		string* line = get_current_line();
		if (line) {
			while (prg_csr.char_ix > line->length()) {
				move_prg_csr_left();
			}
		}
	}
}
void t_program_editor::move_prg_csr_end_x() {
	string* line = get_current_line();
	if (!line) return;
	while (prg_csr.char_ix < line->length()) {
		move_prg_csr_right();
	}
}
void t_program_editor::move_prg_csr_home_x() {
	string* line = get_current_line();
	if (!line) return;
	while (prg_csr.char_ix > 0) {
		move_prg_csr_left();
	}
}
void t_program_editor::move_prg_csr_home() {
	move_prg_csr_home_x();
	while (prg_csr.line_ix > 0) {
		move_prg_csr_up();
	}
}
void t_program_editor::move_prg_csr_end() {
	while (prg_csr.line_ix < prg.src_lines.size() - 1) {
		move_prg_csr_down();
	}
	move_prg_csr_end_x();
}
bool t_program_editor::is_valid_prg_char(int ch) {
	return ch >= 0x20 && ch < 0x7f;
}
void t_program_editor::add_empty_line() {
	prg.src_lines.push_back("");
}
void t_program_editor::type_char(int ch) {
	if (TKey::Shift()) {
		ch = String::ShiftChar(toupper(ch));
	}
	if (TKey::CapsLock()) {
		ch = toupper(ch);
	}
	string* line = get_current_line();
	if (csr_overwrite && prg_csr.char_ix != line->length()) {
		line->at(prg_csr.char_ix) = ch;
	} else {
		line->insert(line->begin() + prg_csr.char_ix, ch);
	}
	move_prg_csr_right();
}
void t_program_editor::type_crlf() {
	string* line = get_current_line();
	string keep = line->substr(0, prg_csr.char_ix);
	string move = line->substr(prg_csr.char_ix);
	*line = move;
	prg.src_lines.insert(prg.src_lines.begin() + prg_csr.line_ix, keep);
	move_prg_csr_home_x();
	move_prg_csr_down();
}
void t_program_editor::type_backspace() {
	if (prg_csr.char_ix > 0) {
		move_prg_csr_left();
		string* line = get_current_line();
		line->erase(line->begin() + prg_csr.char_ix);
	} else if (prg_csr.line_ix < prg.src_lines.size() && prg_csr.line_ix > 0) {
		string line = *get_current_line();
		prg.src_lines.erase(prg.src_lines.begin() + prg_csr.line_ix);
		move_prg_csr_up();
		move_prg_csr_end_x();
		get_current_line()->append(line);
	}
}
void t_program_editor::type_delete() {
	string* line = get_current_line();
	if (prg_csr.char_ix < line->length()) {
		line->erase(line->begin() + prg_csr.char_ix);
	} else {
		string* line_below = get_line_below();
		if (line_below) {
			string str_line_below = *line_below;
			prg.src_lines.erase(prg.src_lines.begin() + prg_csr.line_ix + 1);
			get_current_line()->append(str_line_below);
		}
	}
}
void t_program_editor::type_pgup() {
	move_prg_csr_home_x();
	for (int i = 0; i < buf->Rows / 2 - 1; i++) {
		move_prg_csr_up();
	}
}
void t_program_editor::type_pgdn() {
	move_prg_csr_home_x();
	for (int i = 0; i < buf->Rows / 2 - 1; i++) {
		move_prg_csr_down();
	}
}
void t_program_editor::new_program() {
	if (unsaved) {
		const auto result = confirm("There are unsaved changes.  Save? (Y/N)");
		if (result == t_confirm_result::yes) save_program(prg_filename);
		else if (result == t_confirm_result::cancel) return;
	}
	prg_filename = "";
	prg.src_lines = std::vector<string>();
	add_empty_line();
	unsaved = false;
	move_prg_csr_home();
	cancel_line_selection();
}
void t_program_editor::reload_program() {
	if (!unsaved) return;
	const auto result = confirm("Reload program? (Y/N)");
	if (result == t_confirm_result::yes) load_program(prg_filename);
}
void t_program_editor::load_program() {
	if (unsaved) {
		const auto result = confirm("There are unsaved changes.  Save? (Y/N)");
		if (result == t_confirm_result::yes) save_program(prg_filename);
		else if (result == t_confirm_result::cancel) return;
	}
	hide_cursor();
	t_input_widget* widget = new t_input_widget(globals, "Load program", color.fg, color.pnl_bg);
	string file = widget->show();
	delete widget;
	if (file.empty()) return;
	load_program(file);
}
void t_program_editor::load_program(string file) {
	if (file.empty()) return;
	if (!File::Exists(file)) {
		alert_error("Load program", "File not found: " + file);
		return;
	}
	prg.load_encrypted(file);
	move_prg_csr_home();
	prg_filename = file;
	unsaved = false;
	cancel_line_selection();
}
void t_program_editor::save_program(string file) {
	if (file.empty()) {
		save_program_as();
	} else {
		prg.save_encrypted(file);
		prg_filename = file;
		unsaved = false;
	}
}
void t_program_editor::save_program_as() {
	hide_cursor();
	t_input_widget* widget = new t_input_widget(
		globals, "Save program", prg_filename, color.fg, color.pnl_bg);
	string file = widget->show();
	delete widget;
	if (file.empty()) return;
	save_program(file);
}
void t_program_editor::compile_and_run() {
	t_compiler compiler;
	compiler.run(&prg);
	if (compiler.errors.empty()) {
		t_machine* machine = new t_machine(wnd);
		machine->perfmon = perfmon;
		machine->snd = snd;
		t_interpreter* interpreter = new t_interpreter();
		interpreter->run(&prg, machine, wnd);
		auto errors = interpreter->errors;
		delete interpreter;
		delete machine;
		if (!errors.empty()) {
			print_errors(errors);
		}
		wnd->SetTitle(PTM_EDITOR_WINDOW_TITLE);
	} else {
		print_errors(compiler.errors);
	}
}
void t_program_editor::print_errors(std::vector<string>& errors) {
	beep();
	string error = errors[0];
	while (running || !cfg->autorun.empty()) {
		draw_screen_base();
		print_border_top("PTM", 0);
		if (cfg->autorun.empty()) {
			print_border_bottom("Press ENTER to continue...", 0);
		} else {
			print_border_bottom("Press ENTER to exit...", 0);
		}
		print(error, 0, 0);
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			running = false;
			break;
		} else if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN) {
				return;
			}
		} else {
			SDL_Delay(1);
		}
	}
}
void t_program_editor::print(string text, int x, int y) {
	x++; y++;
	for (auto& ch : text) {
		if (ch == '\n') {
			x = 1;
			y++;
		} else {
			TTileSeq tile(ch, color.fg, color.bg);
			buf->SetTile(tile, prg_view.layer, x, y, false);
			if (++x > buf->LastCol - 1) {
				break;
			}
		}
	}
}
void t_program_editor::copy_lines(bool cancel_selection) {
	if (!has_selection()) return;
	clipboard.clear();
	auto range = get_line_selection_range();
	for (int i = range.first; i < range.second; i++) {
		clipboard.push_back(prg.src_lines[i]);
	}
	if (cancel_selection) {
		cancel_line_selection();
	}
}
void t_program_editor::cut_lines() {
	if (!has_selection()) return;
	copy_lines(false);
	delete_lines();
}
void t_program_editor::paste_lines() {
	cancel_line_selection();
	for (auto& line : clipboard) {
		prg.src_lines.insert(prg.src_lines.begin() + prg_csr.line_ix, line);
		move_prg_csr_home_x();
		move_prg_csr_down();
	}
}
void t_program_editor::clear_current_line() {
	get_current_line()->clear();
	cancel_line_selection();
}
void t_program_editor::clear_lines() {
	auto range = get_line_selection_range();
	for (int i = range.first; i < range.second; i++) {
		prg.src_lines[i].clear();
	}
}
void t_program_editor::delete_lines() {
	auto range = get_line_selection_range();
	prg.src_lines.erase(prg.src_lines.begin() + range.first, prg.src_lines.begin() + range.second);
	if (prg.src_lines.empty()) {
		add_empty_line();
	}
	if (prg_csr.line_ix > line_selection_start) {
		int dist = range.second - range.first;
		for (int i = 0; i < dist; i++) {
			move_prg_csr_up();
		}
	}
	cancel_line_selection();
}
void t_program_editor::start_line_selection() {
	line_selection_start = prg_csr.line_ix;
}
void t_program_editor::cancel_line_selection() {
	line_selection_start = -1;
}
void t_program_editor::select_entire_program() {
	line_selection_start = 0;
	move_prg_csr_end();
}
std::pair<int, int> t_program_editor::get_line_selection_range() {
	if (!has_selection()) { 
		return std::pair<int, int>(-1, -1); 
	}
	int first = -1;
	int last = -1;
	if (line_selection_start < prg_csr.line_ix) {
		first = line_selection_start;
		last = prg_csr.line_ix;
	} else {
		first = prg_csr.line_ix;
		last = line_selection_start;
	}
	return std::pair<int, int>(first, last);
}
bool t_program_editor::is_selected(int line_ix) {
	auto range = get_line_selection_range();
	return line_ix >= range.first && line_ix < range.second;
}
bool t_program_editor::has_selection() {
	return line_selection_start >= 0;
}
void t_program_editor::show_help() {
	hide_cursor();
	t_panel pnl(buf, color.fg, color.pnl_bg);
	pnl.title = "Help";
	pnl.maximize();
	pnl.center_title();
	
	while (true) {
		pnl.draw_frame();
		pnl.print("PTM\nProgrammable Tile Machine\nVersion 2022.0 (pre-alpha)", 1, 1, color.fg_bold);
		pnl.print("Developed by Fernando Aires Castello", 1, 5, color.fg_bold);
		pnl.print("https://github.com/FernandoAiresCastello", 1, 6, color.fg_bold);
		int x = 1;
		int y = 8;
		pnl.print("F1            Help", x, y++);
		pnl.print("F5            Run program", x, y++);
		pnl.print("CTRL+N        Create new program", x, y++);
		pnl.print("CTRL+L        Load program", x, y++);
		pnl.print("CTRL+S        Save program", x, y++);
		pnl.print("CTRL+SHIFT+S  Save program as", x, y++);
		pnl.print("CTRL+I        Info on/off", x, y++);
		pnl.print("ALT+ENTER     Toggle fullscreen", x, y++);
		pnl.print("ALT+Q         Quit", x, y++);

		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			const auto key = e.key.keysym.sym;
			if (key == SDLK_F1 || key == SDLK_ESCAPE || key == SDLK_RETURN) {
				break;
			} else if (key == SDLK_t) {
				pnl.erase_frame();
				wnd->Update();
				SDL_Delay(1000);
			}
		}
	}
}
t_confirm_result t_program_editor::confirm(string msg) {
	hide_cursor();
	t_confirm_result result = t_confirm_result::cancel;
	const int h = 1;
	const int w = msg.length();
	const int x = (buf->Cols / 2) - (w / 2) - 1;
	const int y = (buf->Rows - 2) / 2;
	t_panel* pnl = new t_panel(buf, x, y, w, h, color.fg, color.pnl_bg);

	while (true) {
		pnl->draw_frame();
		pnl->print(msg, 0, 0);
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			const auto key = e.key.keysym.sym;
			if (key == SDLK_ESCAPE) {
				result = t_confirm_result::cancel;
				break;
			} else if (key == SDLK_n) {
				result = t_confirm_result::no;
				break;
			} else if (key == SDLK_y) {
				result = t_confirm_result::yes;
				break;
			}
		}
	}
	delete pnl;
	return result;
}
void t_program_editor::alert_error(string title, string text) {
	beep();
	hide_cursor();
	t_alert_widget* widget = new t_alert_widget(globals, title, text, color.fg, color.error_bg);
	widget->show();
	delete widget;
}
void t_program_editor::beep() {
	snd->Beep(2500, 100);
}
