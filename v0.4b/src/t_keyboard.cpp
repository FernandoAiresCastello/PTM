#include "t_keyboard.h"

bool t_keyboard::alt()
{
    return SDL_GetModState() & KMOD_ALT;
}
