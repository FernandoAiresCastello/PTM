#include "ptm_keyboard.h"

#define KBMAP(x, y) kbmap[x] = y;
std::map<string, SDL_Scancode> kbmap;
int last_key = 0;

void ptm_init_keyboard()
{
	KBMAP("RIGHT", SDL_SCANCODE_RIGHT);
	KBMAP("LEFT", SDL_SCANCODE_LEFT);
	KBMAP("UP", SDL_SCANCODE_UP);
	KBMAP("DOWN", SDL_SCANCODE_DOWN);
	KBMAP("SPACE", SDL_SCANCODE_SPACE);
	KBMAP("ENTER", SDL_SCANCODE_RETURN);
	KBMAP("ESC", SDL_SCANCODE_ESCAPE);
	KBMAP("TAB", SDL_SCANCODE_TAB);
	KBMAP("BS", SDL_SCANCODE_BACKSPACE);
	KBMAP("INS", SDL_SCANCODE_INSERT);
	KBMAP("DEL", SDL_SCANCODE_DELETE);
	KBMAP("HOME", SDL_SCANCODE_HOME);
	KBMAP("END", SDL_SCANCODE_END);
	KBMAP("PGUP", SDL_SCANCODE_PAGEUP);
	KBMAP("PGDN", SDL_SCANCODE_PAGEDOWN);
	KBMAP("F1", SDL_SCANCODE_F1);
	KBMAP("F2", SDL_SCANCODE_F2);
	KBMAP("F3", SDL_SCANCODE_F3);
	KBMAP("F4", SDL_SCANCODE_F4);
	KBMAP("F5", SDL_SCANCODE_F5);
	KBMAP("F6", SDL_SCANCODE_F6);
	KBMAP("F7", SDL_SCANCODE_F7);
	KBMAP("F8", SDL_SCANCODE_F8);
	KBMAP("F9", SDL_SCANCODE_F9);
	KBMAP("F10", SDL_SCANCODE_F10);
	KBMAP("F11", SDL_SCANCODE_F11);
	KBMAP("F12", SDL_SCANCODE_F12);
	KBMAP("A", SDL_SCANCODE_A);
	KBMAP("B", SDL_SCANCODE_B);
	KBMAP("C", SDL_SCANCODE_C);
	KBMAP("D", SDL_SCANCODE_D);
	KBMAP("E", SDL_SCANCODE_E);
	KBMAP("F", SDL_SCANCODE_F);
	KBMAP("G", SDL_SCANCODE_G);
	KBMAP("H", SDL_SCANCODE_H);
	KBMAP("I", SDL_SCANCODE_I);
	KBMAP("J", SDL_SCANCODE_J);
	KBMAP("K", SDL_SCANCODE_K);
	KBMAP("L", SDL_SCANCODE_L);
	KBMAP("M", SDL_SCANCODE_M);
	KBMAP("N", SDL_SCANCODE_N);
	KBMAP("O", SDL_SCANCODE_O);
	KBMAP("P", SDL_SCANCODE_P);
	KBMAP("Q", SDL_SCANCODE_Q);
	KBMAP("R", SDL_SCANCODE_R);
	KBMAP("S", SDL_SCANCODE_S);
	KBMAP("T", SDL_SCANCODE_T);
	KBMAP("U", SDL_SCANCODE_U);
	KBMAP("V", SDL_SCANCODE_V);
	KBMAP("W", SDL_SCANCODE_W);
	KBMAP("X", SDL_SCANCODE_X);
	KBMAP("Y", SDL_SCANCODE_Y);
	KBMAP("Z", SDL_SCANCODE_Z);
	KBMAP("0", SDL_SCANCODE_0);
	KBMAP("1", SDL_SCANCODE_1);
	KBMAP("2", SDL_SCANCODE_2);
	KBMAP("3", SDL_SCANCODE_3);
	KBMAP("4", SDL_SCANCODE_4);
	KBMAP("5", SDL_SCANCODE_5);
	KBMAP("6", SDL_SCANCODE_6);
	KBMAP("7", SDL_SCANCODE_7);
	KBMAP("8", SDL_SCANCODE_8);
	KBMAP("9", SDL_SCANCODE_9);
}
bool ptm_kb_pressed(SDL_Scancode key)
{
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	return state[key];
}
bool ptm_kb_pressed(string keyname)
{
	keyname = String::ToUpper(keyname);

	if (keyname == "SHIFT") return ptm_kb_shift();
	if (keyname == "CTRL") return ptm_kb_ctrl();
	if (keyname == "ALT") return ptm_kb_alt();
	if (keyname == "CAPS") return ptm_kb_caps();

	return ptm_kb_pressed(kbmap[keyname]);
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
