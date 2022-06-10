#include "t_program_editor.h"
#include "t_editor_screen.h"

t_program_editor::t_program_editor(TBufferedWindow* wnd) {
	exit_requested = false;
	scr = new t_editor_screen(wnd);
}
t_program_editor::~t_program_editor() {
	delete scr;
}
void t_program_editor::print_intro() {
	scr->clear_lines();
	scr->println("PTM 0.1", false);
	print_ok();
}
void t_program_editor::print_debug() {
	scr->debug(
		String::Format("%i %i %s %i %i", 
		scr->csr_x(), scr->csr_y(),
		scr->is_cursor_on_last_line() ? "B" : "-",
		scr->line_count(),
		scr->get_current_line().length()));
}
void t_program_editor::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_RIGHT) {
		if (ctrl) {
			scr->scroll_right();
		} else {
			scr->csr_move(1, 0);
		}
	} else if (key == SDLK_LEFT) {
		if (ctrl) {
			scr->scroll_left();
		} else {
			scr->csr_move(-1, 0);
		}
	} else if (key == SDLK_UP) {
		if (ctrl) {
			scr->scroll_up();
		} else {
			scr->csr_move(0, -1);
		}
	} else if (key == SDLK_DOWN) {
		if (ctrl) {
			scr->scroll_down();
		} else {
			scr->csr_move(0, 1);
		}
	} else if (key == SDLK_BACKSPACE) {
		scr->csr_backspace();
	} else if (key == SDLK_DELETE) {
		if (shift) {
			scr->clear_current_line();
		} else {
			scr->csr_delete();
		}
	} else if (key == SDLK_HOME) {
		if (shift) {
			scr->clear_lines();
		} else if (ctrl) {
			scr->csr_home();
		} else {
			scr->csr_line_start();
		}
	} else if (key == SDLK_END) {
		if (ctrl) {
			scr->csr_end();
		} else {
			scr->csr_line_end();
		}
	} else if (key == SDLK_RETURN) {
		string line = scr->get_current_string();
		scr->crlf();
		if (!line.empty()) {
			process_line(line);
		}
	} else if (key >= 0x20 && key < 0x7f) {
		if (shift) {
			scr->type_char(String::ShiftChar(toupper(key)), false, true);
		} else {
			scr->type_char(TKey::CapsLock() ? toupper(key) : key, false, true);
		}
	} else if (key == SDLK_TAB) {
		for (int i = 0; i < 4; i++) {
			scr->type_char(' ', false, true);
		}
	} else if (key == SDLK_F1) {
		scr->print("SAVE \"\"", false);
		scr->csr_move(-1, 0);
	} else if (key == SDLK_F2) {
		scr->print("LOAD \"\"", false);
		scr->csr_move(-1, 0);
	} else if (key == SDLK_F3) {
		scr->print("COLOR ", false);
	} else if (key == SDLK_F4) {
		scr->print("LIST ", false);
	} else if (key == SDLK_F5) {
		scr->print("RUN ", false);
	} else if (key == SDLK_F6) {
		scr->print("RENUM ", false);
	}
}
void t_program_editor::print_ok() {
	scr->println("Ok", true);
}
void t_program_editor::print_msg(string msg) {
	scr->println(msg, true);
	print_ok();
}
void t_program_editor::print_error(string error) {
	print_msg(error);
}
void t_program_editor::print_program_line(t_program_line* line) {
	scr->println(String::Format("%i %s", line->number, line->src.c_str()), true);
}
void t_program_editor::process_line(string line) {
	line = String::Trim(line);
	if (String::StartsWithNumber(line)) {
		store_program_line(line);
	} else {
		execute_command(line);
	}
}
void t_program_editor::execute_command(string line) {
	if (line.empty()) { 
		return; 
	}
	string cmd = "";
	std::vector<string> args;
	int ixSpace = String::FindFirst(line, ' ');
	if (ixSpace >= 0) {
		auto cmdParts = String::Split(line, ' ', true);
		cmd = cmdParts[0];
		args = String::Split(cmdParts[1], ',', true);
	} else {
		cmd = line;
	}
	cmd = String::ToUpper(cmd);

	if (cmd == "FGCOLOR") {
		if (assert_argc(args, 1)) {
			int fg = String::ToInt(args[0]);
			if (assert_color_ix(fg)) {
				scr->color.fg = fg;
				print_ok();
			}
		}
	} else if (cmd == "BGCOLOR") {
		if (assert_argc(args, 1)) {
			int bg = String::ToInt(args[0]);
			if (assert_color_ix(bg)) {
				scr->color.bg = bg;
				print_ok();
			}
		}
	} else if (cmd == "BDCOLOR") {
		if (assert_argc(args, 1)) {
			int bdr = String::ToInt(args[0]);
			if (assert_color_ix(bdr)) {
				scr->color.bdr = bdr;
				print_ok();
			}
		}
	} else if (cmd == "COLOR") {
		if (assert_argc(args, 3)) {
			int fg = String::ToInt(args[0]);
			if (assert_color_ix(fg)) {
				scr->color.fg = fg;
			} else {
				return;
			}
			int bg = String::ToInt(args[1]);
			if (assert_color_ix(bg)) {
				scr->color.bg = bg;
			} else {
				return;
			}
			int bdr = String::ToInt(args[2]);
			if (assert_color_ix(bdr)) {
				scr->color.bdr = bdr;
			} else {
				return;
			}
			print_ok();
		}
	} else if (cmd == "EXIT") {
		if (assert_argc(args, 0)) {
			exit_requested = true;
			print_ok();
		}
	} else if (cmd == "LIST") {
		if (args.empty()) {
			for (auto& line : prg.lines) {
				print_program_line(&line);
			}
			print_ok();
		} else if (args.size() == 1) {
			int line_nr = String::ToInt(args[0]);
			auto line = prg.get_line(line_nr);
			if (line) {
				print_program_line(line);
				print_ok();
			} else {
				print_error("Line not found");
			}
		} else if (args.size() == 2) {
			int begin = String::ToInt(args[0]);
			int end = String::ToInt(args[1]);
			for (int i = begin; i <= end; i++) {
				auto line = prg.get_line(i);
				if (line) {
					print_program_line(line);
				}
			}
			print_ok();
		}
	} else if (cmd == "RENUM") {
		if (assert_argc(args, 1)) {
			int increment = String::ToInt(args[0]);
			if (increment > 0) {
				prg.renumerate(increment);
				print_ok();
			} else {
				print_error("Illegal increment");
			}
		}
	} else {
		print_error("Syntax error");
		return;
	}
}
bool t_program_editor::assert_color_ix(int ix) {
	if (ix < 0 || ix >= scr->palette->GetSize()) {
		print_error("Invalid color index");
		return false;
	}
	return true;
}
bool t_program_editor::assert_argc(std::vector<string>& args, int argc) {
	if (args.size() < argc) {
		print_error("Missing arguments");
		return false;
	} else if (args.size() > argc) {
		print_error("Too many arguments");
		return false;
	}
	return true;
}
void t_program_editor::store_program_line(string line) {
	int number = 0;
	line = String::Trim(line);
	bool emptyLine = false;
	int ixSpace = String::FindFirst(line, ' ');
	if (ixSpace >= 0) {
		auto firstChars = String::GetFirstChars(line, ixSpace);
		auto lineNr = String::Trim(firstChars);
		number = String::ToInt(lineNr);
	} else {
		emptyLine = true;
		number = String::ToInt(line);
	}
	if (number <= 0) {
		print_error("Illegal line number");
		return;
	}
	if (emptyLine) {
		if (prg.has_line_number(number)) {
			prg.delete_line(number);
			print_msg(String::Format("Line %i deleted", number));
		} else {
			print_error("Line not found");
		}
		return;
	}
	prg.add_line(number, String::Trim(line.substr(ixSpace)));
	scr->csr_line_start();
}
