#include "t_program_editor.h"
#include "t_editor_screen.h"

t_program_editor::t_program_editor(TBufferedWindow* wnd) {
	scr = new t_editor_screen(wnd);
}
t_program_editor::~t_program_editor() {
	delete scr;
}
void t_program_editor::print_intro() {
	scr->clear();
	scr->print("   Hello World!\nSecond line");
	scr->set_cursor(0, 0);
}
void t_program_editor::draw() {
	scr->draw_border();
	scr->draw_cursor();
}
void t_program_editor::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_RIGHT) {
		scr->move_cursor(1, 0);
	} else if (key == SDLK_LEFT) {
		scr->move_cursor(-1, 0);
	} else if (key == SDLK_UP) {
		scr->move_cursor(0, -1);
	} else if (key == SDLK_DOWN) {
		scr->move_cursor(0, 1);
	} else if (key == SDLK_RETURN) {
		string line = get_line_at_cursor();
		scr->new_line();
		if (!line.empty()) {
			process_line(line);
		}
	} else if (key >= 0x20 && key < 0x7f) {
		scr->put_char(key);
	}
}
string t_program_editor::get_line_at_cursor() {
	string line;
	for (int x = 0; x < scr->cols - 1; x++) {
		auto& tile = scr->get_tile_at(x, scr->get_cursor_y());
		if (!tile.IsEmpty()) {
			int chr = tile.GetChar(0);
			if (chr >= 0x20 && chr < 0xff) {
				line += chr;
			}
			else {
				line += ' ';
			}
		} else {
			line += ' ';
		}
	}
	return String::Trim(line);
}
void t_program_editor::process_line(string line) {
	scr->println("Syntax error");
	scr->println("Ok");
}
