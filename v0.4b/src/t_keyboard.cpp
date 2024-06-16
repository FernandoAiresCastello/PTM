#include "t_keyboard.h"

bool t_keyboard::is_pressed(SDL_Scancode key)
{
    return SDL_GetKeyboardState(nullptr)[key];
}

bool t_keyboard::alt()
{
    return SDL_GetModState() & KMOD_ALT;
}
