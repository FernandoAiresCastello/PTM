#pragma once
#include "common.h"

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
	t_program_line* cur_line;
	bool running;
	bool halted;
	bool user_break;
	int cur_line_ix;
	bool branched;
	t_command* cmd;
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void abort(string error);
	void resolve_vars(t_program_line* line);
	void execute_current_line();
};
