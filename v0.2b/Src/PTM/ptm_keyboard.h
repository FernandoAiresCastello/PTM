#pragma once
#include "../Common/common.h"

extern std::map<string, SDL_Scancode> kbmap;
extern int last_key;

bool ptm_kb_pressed(SDL_Scancode key);
bool ptm_kb_pressed(string keyname);
bool ptm_kb_shift();
bool ptm_kb_ctrl();
bool ptm_kb_alt();
bool ptm_kb_caps();
bool ptm_kb_numlock();
bool ptm_kb_scrlock();
char ptm_keycode_to_char(SDL_Keycode key);
