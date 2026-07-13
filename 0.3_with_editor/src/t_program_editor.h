#pragma once
#include <SDL.h>
#include "t_list.h"
#include "t_string.h"

class PTM;
class t_screen;
class t_keyboard;
class t_interpreter;
class t_sound;

class t_program_editor
{
public:
	bool active = false;

	t_program_editor();
	~t_program_editor();

	void init(PTM* ptm, t_screen* scr, t_keyboard* kb);
	void reset();
	void on_keydown();
	void draw_program();

private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;
	t_sound* snd = nullptr;

	t_list<t_string> lines;
	int cur_line_ix = 0;
	int first_line_ix = 0;
	int last_line_ix = 0;

	void on_enter_pressed();
};
