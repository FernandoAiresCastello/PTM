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
