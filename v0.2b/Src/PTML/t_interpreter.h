#pragma once
#include "../Common/common.h"
#include "t_param.h"
#include "t_loop.h"
#include "t_variable.h"

#define ARGC(x)				if (!intp->argc(arg, x)) return;
#define ARGC_MIN_MAX(x, y)	if (!intp->argc(arg, x, y)) return;

struct t_program;
struct t_program_line;

struct t_interpreter {

	void (*on_idle_loop)() = nullptr;
	void (*on_keydown)(SDL_Keycode) = nullptr;
	void (*on_exec_line)(t_program_line*, string&, t_params&) = nullptr;
	std::vector<string> errors;
	unordered_map<string, t_variable> vars;
	unordered_map<string, vector<string>> arrays;

	t_interpreter();
	void run(t_program* prg);
	void abort(string error);
	bool argc(t_params& arg, int expected);
	bool argc(t_params& arg, int min, int max);
	int require_number(t_param& arg);
	string require_label(t_param& arg);
	string require_id(t_param& arg);
	string require_existing_varname(t_param& arg);
	string require_string(t_param& arg);
	string require_existing_array(t_param& arg);
	string require_array_element(t_param& arg);
	int require_array_index(std::vector<string>& arr, string arr_id, t_param& arg);
	void goto_label(string label);
	void call_label(string label);
	void return_from_call();
	void loop_start(string var, int first, int last, int step);
	void array_loop_start(string arr_id, string iter_var);
	void loop_end();
	void loop_break();
	void loop_continue();
	void goto_matching_endif();

private:

	bool running;
	bool halted;
	bool reset_requested = false;
	int pause_cycles = 0;
	int cur_line_ix;
	bool branched;
	t_program* prg;
	t_program_line* cur_line;
	stack<int> callstack;
	stack<t_loop> loopstack;
	stack<int> ifstack;
	SDL_Keycode last_keycode_pressed = 0;

	void execute_current_line();
};
