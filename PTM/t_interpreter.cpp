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
	cmd = new t_command(this);
	running = true;
	halted = false;
	branched = false;
	user_break = false;
	cur_line_ix = 0;
	callstack = std::stack<int>();
	this->wnd = wnd;
	wnd_buf = wnd->GetBuffer();
	wnd_buf->ClearAllLayers();

	while (running) {
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			on_keydown(e.key.keysym.sym, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		}
		machine->update_window(wnd);
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
			abort("Invalid execution pointer");
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
int t_interpreter::require_number(t_param& arg) {
	if (arg.type == t_param_type::number || 
		arg.type == t_param_type::string || 
		arg.type == t_param_type::char_literal) {
		return arg.numeric_value;
	} else if (arg.type == t_param_type::address_alias) {
		if (has_address_alias(arg.address_alias)) {
			return get_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_alias) {
		if (has_address_alias(arg.address_alias)) {
			return peek_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_literal) {
		return machine->peek(arg.address);
	} else {
		abort("Syntax error");
	}
	return 0;
}
string t_interpreter::require_label(t_param& arg) {
	if (arg.type != t_param_type::label) {
		abort("Label expected");
		return "";
	}
	if (prg->labels.find(arg.label) == prg->labels.end()) {
		abort("Label not found");
		return "";
	}
	return arg.label;
}
int t_interpreter::require_adress_or_alias(t_param& arg) {
	if (arg.type == t_param_type::number) {
		return arg.numeric_value;
	} else if (arg.type == t_param_type::address_alias) {
		if (has_address_alias(arg.address_alias)) {
			return get_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else {
		abort("Address or alias expected");
	}
	return ILLEGAL_ADDRESS;
}
int t_interpreter::require_aliased_address(t_param& arg) {
	if (arg.type == t_param_type::address_alias) {
		if (has_address_alias(arg.address_alias)) {
			return get_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else {
		abort("Alias expected");
	}
	return ILLEGAL_ADDRESS;
}
string t_interpreter::require_string(t_param& arg) {
	if (arg.type == t_param_type::string || arg.type == t_param_type::number) {
		return arg.textual_value;
	} else if (arg.type == t_param_type::address_alias) {
		if (has_address_alias(arg.address_alias)) {
			return String::ToString(get_address_with_alias(arg.address_alias));
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_alias) {
		if (has_address_alias(arg.address_alias)) {
			return get_string_from_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_literal) {
		return get_string_from_address(arg.address);
	} else {
		abort("String expected");
	}
	return "";
}
bool t_interpreter::has_address_alias(string alias) {
	return address_alias.find(alias) != address_alias.end();
}
int t_interpreter::get_address_with_alias(string alias) {
	return has_address_alias(alias) ? address_alias[alias] : ILLEGAL_ADDRESS;
}
int t_interpreter::peek_address_with_alias(string alias) {
	return machine->memory[get_address_with_alias(alias)];
}
void t_interpreter::poke_address_with_alias(string alias, int value) {
	if (has_address_alias(alias)) {
		machine->memory[get_address_with_alias(alias)] = value;
	}
}
string t_interpreter::get_string_from_address_with_alias(string alias) {
	return get_string_from_address(get_address_with_alias(alias));
}
string t_interpreter::get_string_from_address(int start_address) {
	string str = "";
	int addr = start_address;
	bool scanning = true;
	while (scanning) {
		int ch = machine->memory[addr];
		if (ch <= 0) {
			scanning = false;
		} else if (ch <= 255) {
			str += (char)ch;
		}
		addr++;
		if (addr >= MEMORY_TOP) {
			scanning = false;
		}
	}
	return str;
}
