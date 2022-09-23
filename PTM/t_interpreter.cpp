#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_machine.h"
#include "t_command.h"

t_interpreter::t_interpreter() {
	wnd = nullptr;
	wnd_buf = nullptr;
	running = false;
	halted = false;
	branched = false;
	machine = nullptr;
	cur_line_ix = 0;
	cmd = nullptr;
	cur_line = nullptr;
	prg = nullptr;
}
void t_interpreter::run(t_program* prg, t_machine* machine, TBufferedWindow* wnd) {
	errors.clear();
	this->prg = prg;
	this->machine = machine;
	this->wnd = wnd;
	machine->intp = this;
	running = true;
	halted = false;
	branched = false;
	cur_line_ix = 0;
	cmd = new t_command(this);
	callstack = std::stack<int>();

	while (running) { // This loop needs to be fast!
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);

		if (e.type == SDL_QUIT) {
			running = false;
			break;
		} else if (e.type == SDL_KEYDOWN) {
			on_keydown(e.key.keysym.sym, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		}
		if (halted || pause_cycles > 0) {
			pause_cycles--;
			continue;
		}
		machine->on_loop();
		if (cur_line_ix >= 0 && cur_line_ix < prg->lines.size()) {
			cur_line = &prg->lines[cur_line_ix];
			execute_current_line();
			if (branched) {
				branched = false;
			} else {
				cur_line_ix++;
			}
		} else {
			halted = true;
		}
	}

	delete cmd;
}
void t_interpreter::execute_current_line() {
	string& c = cur_line->cmd;
	if (c.empty()) return;
	auto& args = cur_line->params;
	if (!cmd->execute(c, args)) {
		abort("Invalid command: " + c);
	}
}
void t_interpreter::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_RETURN && TKey::Alt()) {
		wnd->ToggleFullscreen();
	} else if (machine->exit_key != 0 && key == machine->exit_key) {
		running = false;
	} else {
		machine->last_keycode_pressed = key;
	}
}
void t_interpreter::abort(string error) {
	running = false;
	if (cur_line) {
		errors.push_back(String::Format("%s\n\nFile: %s\nLine: %i\nSource:\n\n%s",
			error.c_str(), cur_line->file.c_str(), cur_line->src_line_nr, cur_line->src.c_str()));
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
		abort("Label not found: " + arg.id);
		return "";
	}
	return arg.id;
}
string t_interpreter::require_id(t_param& arg) {
	if (arg.type != t_param_type::id) {
		abort("Identifier expected: " + arg.src);
		return "";
	}
	return arg.id;
}
string t_interpreter::require_existing_varname(t_param& arg) {
	if (arg.is_array_element_ix()) {
		if (machine->arrays.find(arg.id) == machine->arrays.end()) {
			abort("Array not found: " + arg.id);
			return "";
		}
	} else if (arg.type != t_param_type::id) {
		abort("Variable name expected");
		return "";
	}
	if (machine->vars.find(arg.id) == machine->vars.end()) {
		abort("Variable not found: " + arg.id);
		return "";
	}
	return arg.id;
}
int t_interpreter::require_number(t_param& arg) {
	int number = PTM_INVALID_NUMBER;
	if (arg.type == t_param_type::number || 
		arg.type == t_param_type::string || 
		arg.type == t_param_type::char_literal) {
		number = arg.numeric_value;
	} else if (arg.type == t_param_type::id) {
		if (machine->vars.find(arg.id) != machine->vars.end()) {
			number = String::ToInt(machine->vars[arg.id].value);
		} else {
			abort("Variable not found: " + arg.id);
		}
	} else if (arg.is_array_element_ix()) {
		string value = require_array_element(arg);
		number = String::ToInt(value);
	} else {
		abort("Numeric value expected");
	}
	return number;
}
string t_interpreter::require_string(t_param& arg) {
	if (arg.type == t_param_type::string || arg.type == t_param_type::number) {
		return arg.textual_value;
	} else if (arg.type == t_param_type::id) {
		if (machine->vars.find(arg.id) != machine->vars.end()) {
			return machine->vars[arg.id].value;
		} else {
			abort("Variable not found: " + arg.id);
		}
	} else if (arg.is_array_element_ix()) {
		return require_array_element(arg);
	} else {
		abort("String expected");
	}
	return "";
}
string t_interpreter::require_existing_array(t_param& arg) {
	if (machine->arrays.find(arg.id) != machine->arrays.end()) {
		return arg.id;
	} else {
		abort("Array not found: " + arg.id);
	}
	return "";
}
string t_interpreter::require_array_element(t_param& arg) {
	if (!arg.is_array_element_ix()) {
		abort("Array expected");
		return "";
	}
	if (machine->arrays.find(arg.id) == machine->arrays.end()) {
		abort("Array not found: " + arg.id);
		return "";
	}
	auto& src_arr = machine->arrays[arg.id];
	if (arg.type == t_param_type::arr_ix_literal) {
		int ix = arg.arr_ix_literal;
		if (ix >= 0 && ix < src_arr.size()) {
			return src_arr[ix];
		} else {
			abort(String::Format("Array index out of bounds: %i", ix));
		}
	} else if (arg.type == t_param_type::arr_ix_var) {
		string ix_var_id = arg.arr_ix_var;
		if (machine->vars.find(ix_var_id) == machine->vars.end()) {
			abort("Variable not found: " + ix_var_id);
			return "";
		}
		int ix = String::ToInt(machine->vars[ix_var_id].value);
		if (ix >= 0 && ix < src_arr.size()) {
			return src_arr[ix];
		} else {
			abort(String::Format("Array index out of bounds: %i", ix));
		}
	}
	return "";
}
int t_interpreter::require_array_index(std::vector<string>& arr, t_param& arg) {
	int index = PTM_INVALID_NUMBER;

	if (arg.type == t_param_type::arr_ix_literal) {
		index = arg.arr_ix_literal;
	} else if (arg.type == t_param_type::arr_ix_var) {
		string ix_var_id = arg.arr_ix_var;
		if (machine->vars.find(ix_var_id) != machine->vars.end()) {
			index = String::ToInt(machine->vars[ix_var_id].value);
		} else {
			abort("Variable not found: " + ix_var_id);
		}
	} else {
		abort("Array index expected");
	}

	if (index < 0 || index >= arr.size()) {
		abort(String::Format("Array index out of bounds: %i", index));
		index = PTM_INVALID_NUMBER;
	}
	return index;
}
void t_interpreter::goto_label(string label) {
	cur_line_ix = prg->labels[label];
	branched = true;
}
void t_interpreter::call_label(string label) {
	callstack.push(cur_line_ix + 1);
	cur_line_ix = prg->labels[label];
	branched = true;
}
void t_interpreter::return_from_call() {
	if (!callstack.empty()) {
		cur_line_ix = callstack.top();
		callstack.pop();
		branched = true;
	} else {
		abort("Call stack is empty");
	}
}
int t_interpreter::require_charset_ix(t_param& arg) {
	int ix = require_number(arg);
	if (machine->is_valid_charset_ix(ix)) {
		return ix;
	}
	abort(String::Format("Invalid charset index: %i", ix));
	return PTM_INVALID_NUMBER;
}
int t_interpreter::require_palette_ix(t_param& arg) {
	int ix = require_number(arg);
	if (machine->is_valid_palette_ix(ix)) {
		return ix;
	}
	abort(String::Format("Invalid palette index: %i", ix));
	return PTM_INVALID_NUMBER;
}
int t_interpreter::require_tile_frame_ix(TTileSeq& tile, t_param& arg) {
	int frame = require_number(arg);
	if (frame >= 0 && frame < tile.GetSize()) {
		return frame;
	}
	abort(String::Format("Tile frame index out of bounds: %i", frame));
	return PTM_INVALID_NUMBER;
}
void t_interpreter::loop_start(string var, int first, int last, int step) {
	machine->set_var(var, first);
	t_loop loop;
	loop.is_array = false;
	loop.line_ix_begin = cur_line_ix + 1;
	loop.var = var;
	loop.current = first;
	loop.first = first;
	loop.last = last;
	loop.step = step;
	loopstack.push(loop);
}
void t_interpreter::array_loop_start(string arr_id, string iter_var) {
	auto& arr = machine->arrays[arr_id];
	machine->set_var(iter_var, arr[0]);
	t_loop loop;
	loop.is_array = true;
	loop.line_ix_begin = cur_line_ix + 1;
	loop.arr_id = arr_id;
	loop.iter_var = iter_var;
	loop.current = 0;
	loop.first = 0;
	loop.last = arr.size() - 1;
	loop.step = 1;
	loopstack.push(loop);
}
void t_interpreter::loop_end() {
	if (loopstack.empty()) {
		abort("Loop stack is empty");
		return;
	}
	t_loop& loop = loopstack.top();

	if (loop.is_array) {
		if (loop.current >= loop.last) { // Array loop ended
			loopstack.pop();
			return;
		}
		// Next array element
		loop.current++;
		auto& arr = machine->arrays[loop.arr_id];
		machine->vars[loop.iter_var].value = arr[loop.current];

	} else {
		int next_value = loop.current + loop.step;
		if (next_value >= loop.last) { // Loop ended
			loopstack.pop();
			return;
		}
		// Next iteration
		loop.current = next_value;
		machine->vars[loop.var].value = String::ToString(next_value);
	}

	cur_line_ix = loop.line_ix_begin;
	branched = true;
}
void t_interpreter::goto_next_nearest_endif() {
	int endif_ix = -1;
	for (int i = cur_line_ix; i < prg->lines.size(); i++) {
		if (prg->lines[i].is_endif) {
			endif_ix = i;
			break;
		}
	}
	if (endif_ix >= 0) {
		cur_line_ix = endif_ix + 1;
		branched = true;
	} else {
		abort("Missing ENDIF command");
	}
}
