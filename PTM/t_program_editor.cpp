#include "t_program_editor.h"
#include "t_globals.h"
#include "t_config.h"
#include "t_compiler.h"
#include "t_interpreter.h"
#include "t_machine.h"

t_program_editor::t_program_editor(t_globals* g) : t_ui_base(g) {
	csr_overwrite = false;
	prg_view.max_chars = wnd->Cols - 2;
	prg_view.max_lines = wnd->Rows - 2;
	info_visible = true;

	if (!g->cfg->autoload.empty()) {
		if (File::Exists(g->cfg->autoload)) {
			load_program(g->cfg->autoload);
		}
	} else {
		add_empty_line();
	}
}
t_program_editor::~t_program_editor() {
}
void t_program_editor::on_run_loop() {
	draw_screen_base();
	draw_border_info();
	draw_program();
	draw_cursor();
}
void t_program_editor::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (!shift && !ctrl && key != SDLK_DELETE) {
		cancel_line_selection();
	}
	if (TKey::Alt() && key == SDLK_RETURN) {
		wnd->ToggleFullscreen();
	} else if (ctrl && key == SDLK_q) {
		running = false;
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
	} else if (ctrl && key == SDLK_s) {
		save_program(prg_filename);
		unsaved = false;
	} else if (is_valid_prg_char(key)) {
		type_char(key);
		unsaved = true;
	}
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
		bool is_cmd = true;
		int fgc = color.fg;
		auto& line = prg.src_lines[line_ix];
		for (int char_ix = prg_view.first_char_ix; char_ix < prg_view.first_char_ix + prg_view.max_chars && char_ix < line.length(); char_ix++) {
			int ch = line[char_ix];
			if (ch == ' ') {
				is_cmd = false;
			}
			auto trim = String::Trim(line);
			if (String::StartsWith(trim, ";")) {
				fgc = color.comment_fg;
			} else if (String::StartsWith(trim, ":")) {
				fgc = color.label_fg;
			} else {
				if (is_cmd) {
					ch = String::ToUpper(ch);
					fgc = color.cmd_fg;
				} else {
					fgc = color.fg;
				}
			}
			TTileSeq tile(ch, fgc, is_selected(line_ix) ? color.sel_bg : color.bg);
			buf->SetTile(tile, 0, x, y, false);
			if (++x > buf->LastCol - 1) break;
		}
		y++;
	}
}
void t_program_editor::draw_cursor() {
	TTileSeq tile;
	if (csr_overwrite) {
		tile.Add(0xfb, color.csr_fg, color.bg);
	} else {
		tile.Add(0xfc, color.csr_fg, color.bg);
	}
	tile.Add(0x00, color.csr_fg, color.bg);
	buf->SetTile(tile, 1, scr_csr.x, scr_csr.y, true);
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
void t_program_editor::load_program(string file) {
	if (file.empty()) return;
	prg.load_plain(file);
	move_prg_csr_home();
	prg_filename = file;
}
void t_program_editor::save_program(string file) {
	if (file.empty()) return;
	prg.save_plain(file);
	prg_filename = file;
}
void t_program_editor::compile_and_run() {
	save_program(prg_filename);
	t_compiler compiler;
	compiler.run(&prg);
	if (compiler.errors.empty()) {
		t_machine* machine = new t_machine(wnd);
		t_interpreter* interpreter = new t_interpreter();
		interpreter->run(&prg, machine, wnd);
		auto errors = interpreter->errors;
		delete interpreter;
		delete machine;
		if (!errors.empty()) {
			print_errors(errors);
		}
	} else {
		print_errors(compiler.errors);
	}
}
void t_program_editor::print_errors(std::vector<string>& errors) {
	snd->Beep(2500, 100);
	string error = errors[0];
	while (running) {
		draw_screen_base();
		print_border_top("RUNTIME ERROR", 0);
		print_border_bottom("Press ENTER to continue...", 0);
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
			buf->SetTile(tile, 0, x, y, false);
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
