#include "ptm_keyboard.h"

#define KBMAP(x, y) kbmap[x] = y;
map<string, SDL_Scancode> kbmap;
int last_key = 0;

bool ptm_kb_pressed(SDL_Scancode key)
{
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	return state[key];
}
bool ptm_kb_shift()
{
	return SDL_GetModState() & KMOD_SHIFT;
}
bool ptm_kb_ctrl()
{
	return SDL_GetModState() & KMOD_CTRL;
}
bool ptm_kb_alt()
{
	return SDL_GetModState() & KMOD_ALT;
}
bool ptm_kb_caps()
{
	return SDL_GetModState() & KMOD_CAPS;
}
bool ptm_kb_numlock()
{
	return SDL_GetModState() & KMOD_NUM;
}
bool ptm_kb_scrlock()
{
	return SDL_GetModState() & KMOD_SCROLL;
}
char ptm_keycode_to_char(SDL_Keycode key)
{
	bool shift = ptm_kb_shift();

	if (key == SDLK_SPACE) return ' ';

	else if (key >= SDLK_a && key <= SDLK_z) {
		if (ptm_kb_caps() || shift) {
			return toupper(key);
		}
		else {
			return tolower(key);
		}
	}
	else if (key >= SDLK_0 && key <= SDLK_9) {
		if (shift) {
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

	if (key == SDLK_QUOTE) return shift ? '\"' : '\'';
	if (key == SDLK_MINUS || key == SDLK_KP_MINUS) return shift ? '_' : '-';
	if (key == SDLK_EQUALS) return shift ? '+' : '=';
	if (key == SDLK_PLUS || key == SDLK_KP_PLUS) return '+';
	if (key == SDLK_ASTERISK || key == SDLK_KP_MULTIPLY) return '*';
	if (key == SDLK_SLASH || key == SDLK_KP_DIVIDE) return shift ? '?' : '/';
	if (key == SDLK_PERIOD || key == SDLK_KP_PERIOD) return shift ? '>' : '.';
	if (key == SDLK_COMMA || key == SDLK_KP_COMMA) return shift ? '<' : ',';
	if (key == SDLK_SEMICOLON) return shift ? ':' : ';';
	if (key == SDLK_LEFTBRACKET) return shift ? '{' : '[';
	if (key == SDLK_RIGHTBRACKET) return shift ? '}' : ']';
	if (key == SDLK_BACKSLASH) return shift ? '|' : '\\';

	return 0;
}
bool ptm_kb_pressed(string keyname)
{
	keyname = String::ToUpper(keyname);

	// MODIFIERS
	if (keyname == "SHIFT")
		return ptm_kb_shift();
	if (keyname == "CTRL")
		return ptm_kb_ctrl();
	if (keyname == "ALT")
		return ptm_kb_alt();
	if (keyname == "CAPS")
		return ptm_kb_caps();
	if (keyname == "NUMLOCK")
		return ptm_kb_numlock();
	if (keyname == "SCRLOCK")
		return ptm_kb_scrlock();

	// ARROWS
	if (keyname == "RIGHT")
		return ptm_kb_pressed(SDL_SCANCODE_RIGHT);
	if (keyname == "LEFT")
		return ptm_kb_pressed(SDL_SCANCODE_LEFT);
	if (keyname == "UP")
		return ptm_kb_pressed(SDL_SCANCODE_UP);
	if (keyname == "DOWN")
		return ptm_kb_pressed(SDL_SCANCODE_DOWN);

	// CONTROL
	if (keyname == "SPACE")
		return ptm_kb_pressed(SDL_SCANCODE_SPACE);
	if (keyname == "ENTER" || keyname == "RETURN")
		return ptm_kb_pressed(SDL_SCANCODE_RETURN) || ptm_kb_pressed(SDL_SCANCODE_KP_ENTER);
	if (keyname == "ESC")
		return ptm_kb_pressed(SDL_SCANCODE_ESCAPE);
	if (keyname == "TAB")
		return ptm_kb_pressed(SDL_SCANCODE_TAB);
	if (keyname == "BS")
		return ptm_kb_pressed(SDL_SCANCODE_BACKSPACE);
	if (keyname == "INS")
		return ptm_kb_pressed(SDL_SCANCODE_INSERT);
	if (keyname == "DEL")
		return ptm_kb_pressed(SDL_SCANCODE_DELETE);
	if (keyname == "HOME")
		return ptm_kb_pressed(SDL_SCANCODE_HOME);
	if (keyname == "END")
		return ptm_kb_pressed(SDL_SCANCODE_END);
	if (keyname == "PGUP")
		return ptm_kb_pressed(SDL_SCANCODE_PAGEUP);
	if (keyname == "PGDN")
		return ptm_kb_pressed(SDL_SCANCODE_PAGEDOWN);
	if (keyname == "PAUSE" || keyname == "BREAK")
		return ptm_kb_pressed(SDL_SCANCODE_PAUSE);
	if (keyname == "PRINT")
		return ptm_kb_pressed(SDL_SCANCODE_PRINTSCREEN);

	// FUNCTION
	if (keyname == "F1")
		return ptm_kb_pressed(SDL_SCANCODE_F1);
	if (keyname == "F2")
		return ptm_kb_pressed(SDL_SCANCODE_F2);
	if (keyname == "F3")
		return ptm_kb_pressed(SDL_SCANCODE_F3);
	if (keyname == "F4")
		return ptm_kb_pressed(SDL_SCANCODE_F4);
	if (keyname == "F5")
		return ptm_kb_pressed(SDL_SCANCODE_F5);
	if (keyname == "F6")
		return ptm_kb_pressed(SDL_SCANCODE_F6);
	if (keyname == "F7")
		return ptm_kb_pressed(SDL_SCANCODE_F7);
	if (keyname == "F8")
		return ptm_kb_pressed(SDL_SCANCODE_F8);
	if (keyname == "F9")
		return ptm_kb_pressed(SDL_SCANCODE_F9);
	if (keyname == "F10")
		return ptm_kb_pressed(SDL_SCANCODE_F10);
	if (keyname == "F11")
		return ptm_kb_pressed(SDL_SCANCODE_F11);
	if (keyname == "F12")
		return ptm_kb_pressed(SDL_SCANCODE_F12);

	// LETTERS
	if (keyname == "A")
		return ptm_kb_pressed(SDL_SCANCODE_A);
	if (keyname == "B")
		return ptm_kb_pressed(SDL_SCANCODE_B);
	if (keyname == "C")
		return ptm_kb_pressed(SDL_SCANCODE_C);
	if (keyname == "D")
		return ptm_kb_pressed(SDL_SCANCODE_D);
	if (keyname == "E")
		return ptm_kb_pressed(SDL_SCANCODE_E);
	if (keyname == "F")
		return ptm_kb_pressed(SDL_SCANCODE_F);
	if (keyname == "G")
		return ptm_kb_pressed(SDL_SCANCODE_G);
	if (keyname == "H")
		return ptm_kb_pressed(SDL_SCANCODE_H);
	if (keyname == "I")
		return ptm_kb_pressed(SDL_SCANCODE_I);
	if (keyname == "J")
		return ptm_kb_pressed(SDL_SCANCODE_J);
	if (keyname == "K")
		return ptm_kb_pressed(SDL_SCANCODE_K);
	if (keyname == "L")
		return ptm_kb_pressed(SDL_SCANCODE_L);
	if (keyname == "M")
		return ptm_kb_pressed(SDL_SCANCODE_M);
	if (keyname == "N")
		return ptm_kb_pressed(SDL_SCANCODE_N);
	if (keyname == "O")
		return ptm_kb_pressed(SDL_SCANCODE_O);
	if (keyname == "P")
		return ptm_kb_pressed(SDL_SCANCODE_P);
	if (keyname == "Q")
		return ptm_kb_pressed(SDL_SCANCODE_Q);
	if (keyname == "R")
		return ptm_kb_pressed(SDL_SCANCODE_R);
	if (keyname == "S")
		return ptm_kb_pressed(SDL_SCANCODE_S);
	if (keyname == "T")
		return ptm_kb_pressed(SDL_SCANCODE_T);
	if (keyname == "U")
		return ptm_kb_pressed(SDL_SCANCODE_U);
	if (keyname == "V")
		return ptm_kb_pressed(SDL_SCANCODE_V);
	if (keyname == "W")
		return ptm_kb_pressed(SDL_SCANCODE_W);
	if (keyname == "X")
		return ptm_kb_pressed(SDL_SCANCODE_X);
	if (keyname == "Y")
		return ptm_kb_pressed(SDL_SCANCODE_Y);
	if (keyname == "Z")
		return ptm_kb_pressed(SDL_SCANCODE_Z);

	// DIGITS
	if (keyname == "0")
		return ptm_kb_pressed(SDL_SCANCODE_0) || ptm_kb_pressed(SDL_SCANCODE_KP_0);
	if (keyname == "1")
		return ptm_kb_pressed(SDL_SCANCODE_1) || ptm_kb_pressed(SDL_SCANCODE_KP_1);
	if (keyname == "2")
		return ptm_kb_pressed(SDL_SCANCODE_2) || ptm_kb_pressed(SDL_SCANCODE_KP_2);
	if (keyname == "3")
		return ptm_kb_pressed(SDL_SCANCODE_3) || ptm_kb_pressed(SDL_SCANCODE_KP_3);
	if (keyname == "4")
		return ptm_kb_pressed(SDL_SCANCODE_4) || ptm_kb_pressed(SDL_SCANCODE_KP_4);
	if (keyname == "5")
		return ptm_kb_pressed(SDL_SCANCODE_5) || ptm_kb_pressed(SDL_SCANCODE_KP_5);
	if (keyname == "6")
		return ptm_kb_pressed(SDL_SCANCODE_6) || ptm_kb_pressed(SDL_SCANCODE_KP_6);
	if (keyname == "7")
		return ptm_kb_pressed(SDL_SCANCODE_7) || ptm_kb_pressed(SDL_SCANCODE_KP_7);
	if (keyname == "8")
		return ptm_kb_pressed(SDL_SCANCODE_8) || ptm_kb_pressed(SDL_SCANCODE_KP_8);
	if (keyname == "9")
		return ptm_kb_pressed(SDL_SCANCODE_9) || ptm_kb_pressed(SDL_SCANCODE_KP_9);

	// SYMBOLS
	if (keyname == "," || keyname == "<")
		return ptm_kb_pressed(SDL_SCANCODE_COMMA);
	if (keyname == "." || keyname == ">")
		return ptm_kb_pressed(SDL_SCANCODE_PERIOD);
	if (keyname == "/")
		return ptm_kb_pressed(SDL_SCANCODE_KP_DIVIDE);
	if (keyname == "*")
		return ptm_kb_pressed(SDL_SCANCODE_KP_MULTIPLY);
	if (keyname == "+")
		return ptm_kb_pressed(SDL_SCANCODE_KP_PLUS) || ptm_kb_pressed(SDL_SCANCODE_EQUALS);
	if (keyname == "-")
		return ptm_kb_pressed(SDL_SCANCODE_KP_MINUS) || ptm_kb_pressed(SDL_SCANCODE_MINUS);

	return false;
}
