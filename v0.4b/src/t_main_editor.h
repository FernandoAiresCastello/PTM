#pragma once
#include <SDL.h>

class PTM;
class t_screen;
class t_keyboard;

class t_main_editor
{
public:
	void init(PTM* ptm, t_screen* scr, t_keyboard* kb);
	void print_welcome();
	void on_keydown();

private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;

	bool handle_control_key();
	bool handle_function_key();
	bool handle_character_key();
	void highlight_line_wrap();
	void on_enter_pressed();
};
