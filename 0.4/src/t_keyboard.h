#pragma once
#include <SDL.h>
#include "t_string.h"
#include "t_stack.h"

class t_keyboard
{
public:
	t_stack<SDL_Keycode> keystack;
	SDL_Keycode last_key = 0;

	void init();
	inline const Uint8* get_state();
	void push_key(SDL_Keycode key);
	SDL_Keycode peek_key();
	SDL_Keycode pop_key();
	void flush();
	bool is_pressed(SDL_Scancode key);
	bool is_pressed(const t_string& keyname);
	bool shift();
	bool ctrl();
	bool alt();
	bool capslock();
	int keycode_to_char(SDL_Keycode key);
	SDL_Keycode get_keycode_by_name(const t_string& name);
	t_string get_name_by_keycode(SDL_Keycode keycode);
};
