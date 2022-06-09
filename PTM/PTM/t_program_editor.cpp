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
	scr->println("PTM 1.0");
	print_ok();
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
	} else if (key == SDLK_BACKSPACE) {
		scr->move_cursor(-1, 0);
		scr->delete_tile_under_cursor();
	} else if (key == SDLK_DELETE) {
		scr->shift_line_from_cursor();
	} else if (key == SDLK_HOME) {
		if (shift) {
			scr->clear();
		} else if (ctrl) {
			scr->set_cursor(0, 0);
		}
	} else if (key == SDLK_RETURN) {
		string line = scr->get_line_string_at_cursor();
		scr->new_line();
		if (!line.empty()) {
			process_line(line);
		}
	} else if (key >= 0x20 && key < 0x7f) {
		if (shift) {
			scr->put_char(String::ShiftChar(toupper(key)));
		} else {
			scr->put_char(TKey::CapsLock() ? toupper(key) : key);
		}
	}
}
void t_program_editor::print_ok() {
	scr->println("Ok");
}
void t_program_editor::print_msg(string msg) {
	scr->println(msg);
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
				scr->set_fgcolor(fg);
				print_ok();
			}
		}
	} else if (cmd == "BGCOLOR") {
		if (assert_argc(args, 1)) {
			int bg = String::ToInt(arg);
			if (assert_color_ix(bg)) {
				scr->set_bgcolor(bg);
				print_ok();
			}
		}
	} else if (cmd == "BDCOLOR") {
		if (assert_argc(args, 1)) {
			int bdr = String::ToInt(arg);
			if (assert_color_ix(bdr)) {
				scr->set_bdrcolor(bdr);
				print_ok();
			}
		}
	} else if (cmd == "EXIT") {
		if (assert_argc(args, 0)) {
			exit_requested = true;
		}
	} else {
		print_error("Syntax error");
		return;
	}
}
bool t_program_editor::assert_color_ix(int ix) {
	if (ix < 0 || ix >= scr->wnd->GetPalette()->GetSize()) {
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
	string code = String::Trim(line.substr(ixSpace));
	prg.add_line(number, code);
}
