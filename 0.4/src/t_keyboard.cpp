#include <ctype.h>
#include "t_keyboard.h"
#include "t_dict.h"

t_dict<t_string, SDL_Scancode> named_scancodes;

#define KN(x)	named_scancodes[#x] = SDL_SCANCODE_##x;

void t_keyboard::init()
{
	KN(RIGHT); KN(LEFT); KN(UP); KN(DOWN);
	KN(SPACE); KN(RETURN); KN(BACKSPACE); KN(TAB); KN(DELETE);
	KN(INSERT); KN(HOME); KN(END); KN(PAGEUP); KN(PAGEDOWN)
	KN(0); KN(1); KN(2); KN(3); KN(4); 
	KN(5); KN(6); KN(7); KN(8); KN(9);
	KN(A); KN(B); KN(C); KN(D); KN(E); KN(F); KN(G); 
	KN(H); KN(I); KN(J); KN(K); KN(L); KN(M); KN(N); 
	KN(O); KN(P); KN(Q); KN(R); KN(S); KN(T); KN(U); 
	KN(V); KN(W); KN(X); KN(Y); KN(Z); 
	KN(F1); KN(F2); KN(F3); KN(F4); KN(F5); KN(F6); 
	KN(F7); KN(F8); KN(F9); KN(F10); KN(F11); KN(F12);
	KN(LSHIFT); KN(RSHIFT); KN(LCTRL); KN(RCTRL); KN(LALT); KN(RALT)
	KN(PAUSE); KN(PRINTSCREEN); KN(ESCAPE)
}

const Uint8* t_keyboard::get_state()
{
	return SDL_GetKeyboardState(nullptr);
}

void t_keyboard::push_key(SDL_Keycode key)
{
	last_key = key;
	keystack.push(key);
}

SDL_Keycode t_keyboard::peek_key()
{
	return keystack.top();
}

SDL_Keycode t_keyboard::pop_key()
{
	if (keystack.empty())
		return 0;

	auto key = keystack.top();
	keystack.pop();
	return key;
}

void t_keyboard::flush()
{
	while (!keystack.empty())
		keystack.pop();
}

bool t_keyboard::is_pressed(SDL_Scancode key)
{
    return SDL_GetKeyboardState(nullptr)[key];
}

bool t_keyboard::is_pressed(const t_string& keyname)
{
	if (named_scancodes.contains(keyname))
		return is_pressed(named_scancodes[keyname]);
	
	return false;
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

int t_keyboard::keycode_to_char(SDL_Keycode key)
{
	const bool shifted = shift();

	if (key == SDLK_SPACE) return ' ';

	else if (key >= SDLK_a && key <= SDLK_z) {
		if (capslock() || shifted) {
			return toupper(key);
		}
		else {
			return tolower(key);
		}
	}
	else if (key >= SDLK_0 && key <= SDLK_9) {
		if (shifted) {
			if (key == SDLK_0) return ')';
			if (key == SDLK_1) return '!';
			if (key == SDLK_2) return '@';
			if (key == SDLK_3) return '#';
			if (key == SDLK_4) return '$';
			if (key == SDLK_5) return '%';
			if (key == SDLK_6) return '~';
			if (key == SDLK_7) return '&';
			if (key == SDLK_8) return '*';
			if (key == SDLK_9) return '(';
		}
		else {
			return key;
		}
	}
	else {
		if (key == SDLK_KP_0) return '0';
		if (key == SDLK_KP_1) return '1';
		if (key == SDLK_KP_2) return '2';
		if (key == SDLK_KP_3) return '3';
		if (key == SDLK_KP_4) return '4';
		if (key == SDLK_KP_5) return '5';
		if (key == SDLK_KP_6) return '6';
		if (key == SDLK_KP_7) return '7';
		if (key == SDLK_KP_8) return '8';
		if (key == SDLK_KP_9) return '9';
	}

	if (key == SDLK_QUOTE) return shifted ? '\"' : '\'';
	if (key == SDLK_MINUS || key == SDLK_KP_MINUS) return shifted ? '_' : '-';
	if (key == SDLK_EQUALS) return shifted ? '+' : '=';
	if (key == SDLK_PLUS || key == SDLK_KP_PLUS) return '+';
	if (key == SDLK_ASTERISK || key == SDLK_KP_MULTIPLY) return '*';
	if (key == SDLK_SLASH || key == SDLK_KP_DIVIDE) return shifted ? '?' : '/';
	if (key == SDLK_PERIOD) return shifted ? '>' : '.';
	if (key == SDLK_KP_PERIOD) return shifted ? '.' : ',';
	if (key == SDLK_COMMA || key == SDLK_KP_COMMA) return shifted ? '<' : ',';
	if (key == SDLK_SEMICOLON) return shifted ? ':' : ';';
	if (key == SDLK_LEFTBRACKET) return shifted ? '{' : '[';
	if (key == SDLK_RIGHTBRACKET) return shifted ? '}' : ']';
	if (key == SDLK_BACKSLASH) return shifted ? '|' : '\\';

	return 0;
}
