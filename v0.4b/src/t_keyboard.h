#pragma once
#include <SDL.h>

class t_keyboard
{
public:
	SDL_Keycode key = 0;

	bool is_pressed(SDL_Scancode key);
	bool shift();
	bool ctrl();
	bool alt();
	bool capslock();
};
