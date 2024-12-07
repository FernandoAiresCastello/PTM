#include <SDL3/SDL.h>
#include "t_mouse.h"

int t_mouse::get_x()
{
	float x = 0.0;
	SDL_GetMouseState(&x, nullptr);
	return x;
}

int t_mouse::get_y()
{
	float y = 0.0;
	SDL_GetMouseState(nullptr, &y);
	return y;
}

bool t_mouse::btn_left()
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(1);
}

bool t_mouse::btn_middle()
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(2);
}

bool t_mouse::btn_right()
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(3);
}
