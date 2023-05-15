#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"

t_interpreter::t_interpreter() {
	running = false;
	halted = false;
	branched = false;
	cur_line_ix = 0;
	cur_line = nullptr;
	prg = nullptr;
}
void t_interpreter::run(t_program* prg) {
	errors.clear();
	this->prg = prg;
	running = true;
	halted = false;
	branched = false;
	cur_line_ix = 0;
	callstack = std::stack<int>();

	while (running) {
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);

		if (e.type == SDL_QUIT) {
			running = false;
			break;
		} else if (e.type == SDL_KEYDOWN) {
			if (on_keydown) 
				on_keydown(e.key.keysym.sym); // callback
		}
		if (halted || pause_cycles > 0) {
			last_keycode_pressed = 0;
			pause_cycles--;
			if (on_idle_loop)
				on_idle_loop(); // callback
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
			halted = true;
		}
	}
}
void t_interpreter::execute_current_line() {
	string& c = cur_line->cmd;
	if (c.empty()) return;
	auto& args = cur_line->params;
	if (on_exec_line) on_exec_line(c, args); // callback
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
		if (arrays.find(arg.id) == arrays.end()) {
			abort("Array not found: " + arg.id);
			return "";
		}
	} else if (arg.type != t_param_type::id) {
		abort("Variable name expected");
		return "";
	}
	if (vars.find(arg.id) == vars.end()) {
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
		if (vars.find(arg.id) != vars.end()) {
			number = String::ToInt(vars[arg.id].value);
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
		if (vars.find(arg.id) != vars.end()) {
			return vars[arg.id].value;
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
	if (arrays.find(arg.id) != arrays.end()) {
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
	if (arrays.find(arg.id) == arrays.end()) {
		abort("Array not found: " + arg.id);
		return "";
	}
	auto& src_arr = arrays[arg.id];
	if (arg.type == t_param_type::arr_ix_literal) {
		int ix = arg.arr_ix_literal;
		if (ix >= 0 && ix < src_arr.size()) {
			return src_arr[ix];
		} else {
			abort(String::Format("Array index out of bounds: %s[%i]", arg.id.c_str(), ix));
		}
	} else if (arg.type == t_param_type::arr_ix_var) {
		string ix_var_id = arg.arr_ix_var;
		if (vars.find(ix_var_id) == vars.end()) {
			abort("Variable not found: " + ix_var_id);
			return "";
		}
		int ix = String::ToInt(vars[ix_var_id].value);
		if (ix >= 0 && ix < src_arr.size()) {
			return src_arr[ix];
		} else {
			abort(String::Format("Array index out of bounds: %s[%i]", arg.id.c_str(), ix));
		}
	}
	return "";
}
int t_interpreter::require_array_index(std::vector<string>& arr, string arr_id, t_param& arg) {
	int index = PTM_INVALID_NUMBER;

	if (arg.type == t_param_type::arr_ix_literal) {
		index = arg.arr_ix_literal;
	} else if (arg.type == t_param_type::arr_ix_var) {
		string ix_var_id = arg.arr_ix_var;
		if (vars.find(ix_var_id) != vars.end()) {
			index = String::ToInt(vars[ix_var_id].value);
		} else {
			abort("Variable not found: " + ix_var_id);
		}
	} else {
		abort("Array index expected");
	}

	if (index < 0 || index >= arr.size()) {
		abort(String::Format("Array index out of bounds: %s[%i]", arr_id.c_str(), index));
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
void t_interpreter::loop_start(string var, int first, int last, int step) {
	if (step == 0) {
		abort("Invalid FOR increment");
		return;
	}
	vars[var] = t_variable(first);
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
	auto& arr = arrays[arr_id];
	vars[iter_var] = t_variable(arr[0]);
	t_loop loop;
	loop.is_array = true;
	loop.line_ix_begin = cur_line_ix + 1;
	loop.arr_id = arr_id;
	loop.iter_var = iter_var;
	loop.current = 0;
	loop.first = 0;
	loop.last = (int)arr.size() - 1;
	loop.step = 1;
	loopstack.push(loop);
}
void t_interpreter::loop_end() {
	if (loopstack.empty()) {
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
		auto& arr = arrays[loop.arr_id];
		vars[loop.iter_var].value = arr[loop.current];

	} else {
		int next_value = loop.current + loop.step;
		if (loop.step > 0) {
			if (next_value >= loop.last) { // Loop ended
				loopstack.pop();
				return;
			}
		} else if (loop.step < 0) {
			if (next_value <= loop.last) { // Loop ended
				loopstack.pop();
				return;
			}
		}
		// Next iteration
		loop.current = next_value;
		vars[loop.var].value = String::ToString(next_value);
	}

	cur_line_ix = loop.line_ix_begin;
	branched = true;
}
void t_interpreter::loop_break() {
	if (loopstack.empty()) {
		return;
	}
	t_loop& loop = loopstack.top();
	loopstack.pop();
	
	int next_ix = -1;
	for (int i = cur_line_ix; i < prg->lines.size(); i++) {
		if (prg->lines[i].is_endfor) {
			next_ix = i;
			break;
		}
	}
	cur_line_ix = next_ix + 1;
	branched = true;
}
void t_interpreter::loop_continue() {
	loop_end();
}
void t_interpreter::goto_matching_endif() {
	int endif_ix = -1;
	for (int i = cur_line_ix; i < prg->lines.size(); i++) {
		if (prg->lines[i].is_if) {
			ifstack.push(i);
		} else if (prg->lines[i].is_endif) {
			if (ifstack.empty()) {
				endif_ix = i;
				break;
			} else {
				ifstack.pop();
				if (ifstack.empty()) {
					endif_ix = i;
					break;
				}
			}
		}
	}
	cur_line_ix = endif_ix + 1;
	branched = true;
}
