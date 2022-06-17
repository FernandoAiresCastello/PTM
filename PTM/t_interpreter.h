#pragma once
#include "common.h"
#include "t_param.h"

struct t_program;
struct t_program_line;
struct t_game;
struct t_command;

struct t_interpreter {
	std::vector<string> errors;
	t_interpreter();
	bool has_user_break();
	void run(t_program* prg, t_game* game, TBufferedWindow* wnd);
private:
	friend struct t_command;
	TBufferedWindow* wnd;
	TTileBuffer* wnd_buf;
	t_game* game;
	t_program* prg;
	t_program_line* cur_line;
	bool running;
	bool halted;
	bool user_break;
	int cur_line_ix;
	bool branched;
	t_command* cmd;
	std::stack<int> callstack;
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void abort(string error);
	bool argc(t_params& arg, int expected);
	bool argc(t_params& arg, int min, int max);
	int require_number(t_param& arg);
	string require_label(t_param& arg);
	int require_adress_or_alias(t_param& arg);
	string require_string(t_param& arg);
	void execute_current_line();
};
