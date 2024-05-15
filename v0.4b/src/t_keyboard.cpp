#include <SDL.h>
#include "t_keyboard.h"

bool t_keyboard::alt()
{
    return SDL_GetModState() & KMOD_ALT;
}

bool t_keyboard::enter()
{
    return SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN];
}
