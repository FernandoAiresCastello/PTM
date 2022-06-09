#pragma once
#include "common.h"

struct t_editor_screen;

struct t_program_editor {
	t_program_editor(TBufferedWindow* wnd);
	~t_program_editor();
	void print_intro();
	void draw();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
private:
	t_editor_screen* scr;
	string get_line_at_cursor();
	void process_line(string line);
};
