#pragma once
#include "common.h"

struct t_program;
struct t_program_line;

struct t_interpreter {
	std::vector<string> errors;
	t_interpreter();
	bool has_user_break();
	void run(t_program* prg, TBufferedWindow* wnd);
private:
	TBufferedWindow* wnd;
	TTileBuffer* wnd_buf;
	bool running;
	bool halted;
	bool user_break;
	int cur_line_ix;
	bool branched;
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void abort(t_program_line* line, string error);
	void resolve_vars(t_program_line* line);
	void argc(t_program_line* line, int expected);
	void argc(t_program_line* line, int min, int max);
	void execute_line(t_program_line* line);
};
