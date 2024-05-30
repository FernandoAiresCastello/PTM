#pragma once
#include <SDL.h>

class t_keyboard
{
public:
	SDL_Keycode key = 0;

	bool alt();
	bool enter();
};
