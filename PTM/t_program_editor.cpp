#include "t_program_editor.h"
#include "t_config.h"
#include "t_editor_screen.h"
#include "t_compiler.h"
#include "t_interpreter.h"

t_program_editor::t_program_editor(
	TBufferedWindow* wnd, TSound* snd, t_config* cfg) {

	exit_requested = false;
	scr = new t_editor_screen(wnd, cfg);
	this->snd = snd;
	print_intro();

	if (!cfg->autorun.empty() && File::Exists(cfg->autorun)) {
		execute_command("RUN \"" + cfg->autorun + "\"");
	} else if (!cfg->autoload.empty() && File::Exists(cfg->autoload)) {
		execute_command("LOAD \"" + cfg->autoload + "\"");
	} else {
		print_ok();
	}
}
t_program_editor::~t_program_editor() {
	delete scr;
}
void t_program_editor::print_intro() {
	scr->clear_lines();
	scr->println("PTM 0.1", false);
}
void t_program_editor::print_debug() {
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
	} else if (key == SDLK_TAB) {
		for (int i = 0; i < 4; i++) {
			scr->type_char(' ', false, true);
		}
	} else if (key == SDLK_t && alt) {
		scr->type_tile(TTileSeq("64,10,20;65,30,40"), false, true);
	} else if (key == SDLK_F1) {
		scr->print("SAVE \"\"", false);
		scr->csr_move(-1, 0);
	} else if (key == SDLK_F2) {
		scr->print("LOAD \"\"", false);
		scr->csr_move(-1, 0);
	} else if (key == SDLK_F3) {
		scr->print("FILES ", false);
	} else if (key == SDLK_F4) {
		scr->print("LIST ", false);
	} else if (key == SDLK_F5) {
		scr->print("RUN ", false);
	} else if (key == SDLK_F6) {
		scr->print("COLOR ", false);
	} else if (key == SDLK_F7) {
		scr->print("RENUM ", false);
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
	snd->Beep(2500, 50);
}
void t_program_editor::print_program_line(t_source_line* line) {
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
			for (auto& line : prg.src_lines) {
				print_program_line(&line);
			}
			print_ok();
		} else if (args.size() == 1) {
			int line_nr = String::ToInt(args[0]);
			auto line = prg.get_src_line(line_nr);
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
				auto line = prg.get_src_line(i);
				if (line) {
					print_program_line(line);
				}
			}
			print_ok();
		} else {
			print_error("Invalid argument count");
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
	} else if (cmd == "FILES") {
		string pattern = "";
		if (args.size() == 1) {
			pattern = "*." + args[0];
		}
		auto files = File::List(".", pattern, false, false);
		for (auto& file : files) {
			if (file != "." && file != "..") {
				scr->println(file, true);
			}
		}
		print_ok();
	} else if (cmd == "SAVE") {
		if (assert_argc(args, 1)) {
			auto file = String::RemoveFirstAndLast(args[0]);
			File::WriteLines(file, prg.get_src_lines());
			print_ok();
		}
	} else if (cmd == "LOAD") {
		if (assert_argc(args, 1)) {
			auto file = String::RemoveFirstAndLast(args[0]);
			if (!File::Exists(file)) {
				print_error("File not found");
				return;
			}
			auto src = File::ReadLines(file, "\r\n");
			prg.src_lines.clear();
			for (auto& src_line : src) {
				if (!String::Trim(src_line).empty()) {
					store_program_line(src_line);
				}
			}
			print_ok();
		}
	} else if (cmd == "NEW") {
		if (assert_argc(args, 0)) {
			prg.src_lines.clear();
			print_ok();
		}
	} else if (cmd == "DELETE") {
		if (assert_argc(args, 1)) {
			auto file = String::RemoveFirstAndLast(args[0]);
			if (!File::Exists(file)) {
				print_error("File not found");
				return;
			}
			File::Delete(file);
			print_ok();
		}
	} else if (cmd == "RUN") {
		if (assert_argc(args, 0)) {
			t_compiler compiler;
			compiler.run(&prg);
			t_interpreter interpreter;
			interpreter.run(&prg, scr->wnd);
			if (interpreter.has_user_break()) {
				print_error("Break");
			} else {
				print_ok();
			}
		}
	} else if (cmd == "CHR") {
		if (args.size() == 1) {
			int ch = String::ToInt(args[0]);
			if (assert_tile_ix(ch)) {
				TTileSeq tile(ch, scr->color.fg, scr->color.bg);
				scr->type_char(tile, true, true);
				scr->type_char('\n', true, true);
				print_ok();
			}
		} else if (args.size() == 2) {
			int begin = String::ToInt(args[0]);
			int end = String::ToInt(args[1]);
			if (assert_tile_ix(begin) && assert_tile_ix(end)) {
				for (int ch = begin; ch <= end; ch++) {
					TTileSeq tile(ch, scr->color.fg, scr->color.bg);
					scr->type_char(tile, true, true);
				}
				scr->type_char('\n', true, true);
				print_ok();
			}
		} else {
			print_error("Invalid argument count");
		}
	} else if (cmd == "PAL") {
		if (args.size() == 1) {
			int ix = String::ToInt(args[0]);
			if (assert_color_ix(ix)) {
				TTileSeq tile(0, ix, ix);
				scr->type_tile(tile, true, true);
				scr->type_char('\n', true, true);
				print_ok();
			}
		} else if (args.size() == 2) {
			int begin = String::ToInt(args[0]);
			int end = String::ToInt(args[1]);
			if (assert_color_ix(begin) && assert_color_ix(end)) {
				for (int ix = begin; ix <= end; ix++) {
					TTileSeq tile(0, ix, ix);
					scr->type_tile(tile, true, true);
				}
				scr->type_char('\n', true, true);
				print_ok();
			}
		} else {
			print_error("Invalid argument count");
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
bool t_program_editor::assert_tile_ix(int ix) {
	if (ix < 0 || ix >= scr->charset->GetSize()) {
		print_error("Invalid char index");
		return false;
	}
	return true;
}
bool t_program_editor::assert_argc(std::vector<string>& args, int argc) {
	if (args.size() != argc) {
		print_error("Invalid argument count");
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
		} else {
			print_error("Line not found");
		}
		return;
	}
	prg.add_src_line(number, String::Trim(line.substr(ixSpace)));
	scr->csr_line_start();
}
