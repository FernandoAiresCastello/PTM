#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_machine.h"
#include "t_command.h"

t_interpreter::t_interpreter() {
	wnd = nullptr;
	wnd_buf = nullptr;
	running = false;
	user_break = false;
	halted = false;
	branched = false;
	machine = nullptr;
	cur_line_ix = 0;
	cmd = nullptr;
	cur_line = nullptr;
	prg = nullptr;
}
bool t_interpreter::has_user_break() {
	return user_break;
}
void t_interpreter::run(t_program* prg, t_machine* machine, TBufferedWindow* wnd) {
	errors.clear();
	this->prg = prg;
	this->machine = machine;
	this->wnd = wnd;
	running = true;
	halted = false;
	branched = false;
	user_break = false;
	cur_line_ix = 0;
	cmd = new t_command(this);
	callstack = std::stack<int>();

	while (running) {
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			on_keydown(e.key.keysym.sym, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		}
		machine->on_loop();
		if (halted) {
			continue;
		}
		if (cur_line_ix >= 0 && cur_line_ix < prg->lines.size()) {
			cur_line = &prg->lines[cur_line_ix];
			execute_current_line();
			if (branched) {
				branched = false;
			} else {
				cur_line_ix++;
			}
		} else {
			cur_line = nullptr;
			running = false;
		}
	}

	delete cmd;
}
void t_interpreter::execute_current_line() {
	string& c = cur_line->cmd;
	if (c.empty()) return;
	auto& args = cur_line->params;
	if (!cmd->execute(c, args)) {
		abort("Invalid command");
	}
}
void t_interpreter::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_RETURN && TKey::Alt()) {
		wnd->ToggleFullscreen();
	} else if (key == SDLK_ESCAPE) {
		user_break = true;
		running = false;
	}
}
void t_interpreter::abort(string error) {
	running = false;
	if (cur_line) {
		errors.push_back(String::Format("At line %i:\n%s\n\n%s",
			cur_line->src_line_nr, error.c_str(), cur_line->src.c_str()));
	} else {
		errors.push_back(error);
	}
}
bool t_interpreter::argc(t_params& arg, int expected) {
	if (arg.size() != expected) {
		abort("Invalid argument count");
		return false;
	}
	return true;
}
bool t_interpreter::argc(t_params& arg, int min, int max) {
	if (arg.size() < min || arg.size() > max) {
		abort("Invalid argument count");
		return false;
	}
	return true;
}
string t_interpreter::require_label(t_param& arg) {
	if (arg.type != t_param_type::id) {
		abort("Label expected");
		return "";
	}
	if (prg->labels.find(arg.id) == prg->labels.end()) {
		abort("Label not found");
		return "";
	}
	return arg.id;
}
string t_interpreter::require_varname(t_param& arg) {
	if (arg.type != t_param_type::id) {
		abort("Variable name expected");
		return "";
	}
	return arg.id;
}
string t_interpreter::require_existing_varname(t_param& arg) {
	if (arg.type != t_param_type::id) {
		abort("Variable name expected");
		return "";
	}
	if (machine->vars.find(arg.id) == machine->vars.end()) {
		abort("Variable not found");
		return "";
	}
	return arg.id;
}
int t_interpreter::require_number(t_param& arg) {
	if (arg.type == t_param_type::number || 
		arg.type == t_param_type::string || 
		arg.type == t_param_type::char_literal) {
		return arg.numeric_value;
	} else if (arg.type == t_param_type::id) {
		if (machine->vars.find(arg.id) != machine->vars.end()) {
			return String::ToInt(machine->vars[arg.id]);
		} else {
			abort("Variable not found");
		}
	} else {
		abort("Syntax error");
	}
	return 0;
}
string t_interpreter::require_string(t_param& arg) {
	if (arg.type == t_param_type::string || arg.type == t_param_type::number) {
		return arg.textual_value;
	} else if (arg.type == t_param_type::id) {
		if (machine->vars.find(arg.id) != machine->vars.end()) {
			return machine->vars[arg.id];
		} else {
			abort("Variable not found");
		}
	} else {
		abort("String expected");
	}
	return "";
}
