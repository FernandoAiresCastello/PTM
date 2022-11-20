#pragma once
#include "common.h"
#include "t_param.h"
#include "t_loop.h"

#define ARGC(x)				if (!intp->argc(arg, x)) return;
#define ARGC_MIN_MAX(x, y)	if (!intp->argc(arg, x, y)) return;

struct t_program;
struct t_program_line;
struct t_machine;
struct t_command;

struct t_interpreter {
	std::vector<string> errors;
	bool reset_requested = false;
	int pause_cycles = 0;
	t_interpreter();
	void run(t_program* prg, t_machine* machine, TBufferedWindow* wnd);
	void process_global_keypress(SDL_Keycode key);
private:
	friend struct t_command;
	friend struct t_machine;
	bool running;
	bool halted;
	int cur_line_ix;
	bool branched;
	TBufferedWindow* wnd;
	TTileBuffer* wnd_buf;
	t_machine* machine;
	t_program* prg;
	t_program_line* cur_line;
	t_command* cmd;
	std::stack<int> callstack;
	std::stack<t_loop> loopstack;
	std::stack<int> ifstack;
	
	void execute_current_line();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
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
	int require_array_index(std::vector<string>& arr, t_param& arg);
	void goto_label(string label);
	void call_label(string label);
	void return_from_call();
	int require_charset_ix(t_param& arg);
	int require_palette_ix(t_param& arg);
	int require_tile_frame_ix(TTileSeq& tile, t_param& arg);
	void loop_start(string var, int first, int last, int step);
	void array_loop_start(string arr_id, string iter_var);
	void loop_end();
	void loop_break();
	void loop_continue();
	void goto_matching_endif();
};
