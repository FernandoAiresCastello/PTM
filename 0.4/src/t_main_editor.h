#pragma once
#include <SDL.h>
#include "t_dict.h"
#include "t_string.h"

class PTM;
class t_screen;
class t_keyboard;
class t_interpreter;

class t_main_editor
{
public:
	t_dict<SDL_Keycode, t_string> function_keys;
	t_dict<SDL_Keycode, t_string> function_keys_shifted;

	void init(PTM* ptm, t_screen* scr, t_keyboard* kb, t_interpreter* intp);
	void reset();
	void print_welcome();
	void on_keydown();

private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;
	t_interpreter* intp = nullptr;

	bool handle_control_key();
	bool handle_function_key();
	bool handle_character_key();
	bool handle_ctrl_character_key();
	void highlight_line_wrap();
	void on_enter_pressed();
	void trigger_function_key(SDL_Keycode key, bool shift);
};
