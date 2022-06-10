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
void t_program_editor::process_line(string line) {
	if (String::StartsWithNumber(line)) {
		store_program_line(line);
	} else {
		execute_command(line);
	}
}
void t_program_editor::execute_command(string line) {
	if (String::Trim(line).empty()) return;
	string cmd = "";
	string arg = "";
	std::vector<string> args;
	int ixSpace = String::FindFirst(line, ' ');
	if (ixSpace >= 0) {
		auto cmdParts = String::Split(line, ' ', true);
		cmd = cmdParts[0];
		args = String::Split(cmdParts[1], ',', true);
		if (!args.empty()) {
			arg = args[0];
		}
	} else {
		cmd = line;
	}
	cmd = String::ToUpper(cmd);

	if (cmd == "FGCOLOR") {
		if (assert_argc(args, 1)) {
			int fg = String::ToInt(arg);
			if (assert_color_ix(fg)) {
				scr->color.fg = fg;
				print_ok();
			}
		}
	} else if (cmd == "BGCOLOR") {
		if (assert_argc(args, 1)) {
			int bg = String::ToInt(arg);
			if (assert_color_ix(bg)) {
				scr->color.bg = bg;
				print_ok();
			}
		}
	} else if (cmd == "BDCOLOR") {
		if (assert_argc(args, 1)) {
			int bdr = String::ToInt(arg);
			if (assert_color_ix(bdr)) {
				scr->color.bdr = bdr;
				print_ok();
			}
		}
	} else if (cmd == "EXIT") {
		if (assert_argc(args, 0)) {
			exit_requested = true;
			print_ok();
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
