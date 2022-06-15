#pragma once
#include "common.h"

struct t_program;

struct t_interpreter {
	t_interpreter();
	bool has_user_break();
	void run(t_program* prg, TBufferedWindow* wnd);
private:
	TBufferedWindow* wnd;
	TTileBuffer* wnd_buf;
	bool running;
	bool user_break;
	int cur_line_ix;
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
};
