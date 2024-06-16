#pragma once
#include <SDL.h>

class t_keyboard
{
public:
	bool is_pressed(SDL_Scancode key);
	bool alt();
};
