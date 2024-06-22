#include "t_keyboard.h"

bool t_keyboard::is_pressed(SDL_Scancode key)
{
    return SDL_GetKeyboardState(nullptr)[key];
}

bool t_keyboard::shift()
{
    return SDL_GetModState() & KMOD_SHIFT;
}

bool t_keyboard::ctrl()
{
    return SDL_GetModState() & KMOD_CTRL;
}

bool t_keyboard::alt()
{
    return SDL_GetModState() & KMOD_ALT;
}

bool t_keyboard::capslock()
{
    return SDL_GetModState() & KMOD_CAPS;
}
