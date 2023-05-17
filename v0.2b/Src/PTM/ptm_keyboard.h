#pragma once
#include "../Common/common.h"

extern std::map<string, SDL_Scancode> kbmap;

void ptm_init_keyboard();
bool ptm_kb_pressed(SDL_Scancode key);
bool ptm_kb_pressed(string keyname);
bool ptm_kb_shift();
bool ptm_kb_ctrl();
bool ptm_kb_alt();
bool ptm_kb_caps();
