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
		prg.src_lines.push_back("");
	}
}
void t_program_editor::on_run_loop() {
	draw_screen_base();
	draw_border_info();
	draw_program();
	draw_cursor();
}
void t_program_editor::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_ESCAPE) {
		running = false;
	} else if (TKey::Alt() && key == SDLK_RETURN) {
		wnd->ToggleFullscreen();
	} else if (key == SDLK_RIGHT) {
		move_prg_csr_right();
	} else if (key == SDLK_LEFT) {
		move_prg_csr_left();
	} else if (key == SDLK_DOWN) {
		move_prg_csr_down();
	} else if (key == SDLK_UP) {
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
	} else if (key == SDLK_BACKSPACE) {
		type_backspace();
	} else if (key == SDLK_DELETE) {
		type_delete();
	} else if (key == SDLK_F1) {
		info_visible = !info_visible;
	} else if (key == SDLK_F5) {
		compile_and_run();
	} else if (is_valid_prg_char(key)) {
		type_char(key);
	}
}
void t_program_editor::draw_border_info() {
	if (!info_visible) return;
	print_border_top(prg_filename, 0);
	print_border_bottom(String::Format("L:%i/%i C:%i", 
		prg_csr.line_ix + 1, prg.src_lines.size(), prg_csr.char_ix), 0);
	print_border_bottom(csr_overwrite ? "ovr" : "ins", 27);
}
void t_program_editor::draw_program() {
	int x = 1;
	int y = 1;
	for (int line_ix = prg_view.first_line_ix; line_ix < prg_view.first_line_ix + prg_view.max_lines && line_ix < prg.src_lines.size(); line_ix++) {
		x = 1;
		auto& line = prg.src_lines[line_ix];
		for (int char_ix = prg_view.first_char_ix; char_ix < prg_view.first_char_ix + prg_view.max_chars && char_ix < line.length(); char_ix++) {
			int ch = line[char_ix];
			if (ch == '\t') ch = ' ';
			TTileSeq tile(ch, color.fg, color.bg);
			buf->SetTile(tile, 0, x, y, false);
			if (++x > buf->LastCol - 1) break;
		}
		y++;
	}
}
void t_program_editor::draw_cursor() {
	TTileSeq tile;
	int ch = get_char_under_cursor();
	tile.Add(ch, color.bg, color.fg);
	tile.Add(ch, color.fg, color.bg);
	buf->SetTile(tile, 1, scr_csr.x, scr_csr.y, false);
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
		while (prg_csr.char_ix > line->length()) {
			move_prg_csr_left();
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
	prg.load(file);
	move_prg_csr_home();
	prg_filename = file;
}
void t_program_editor::compile_and_run() {
	t_compiler compiler;
	compiler.run(&prg);
	if (compiler.errors.empty()) {
		t_machine* machine = new t_machine();
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
