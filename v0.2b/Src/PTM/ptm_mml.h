#pragma once
#include "../Common/common.h"

void ptm_init_mml();
void ptm_destroy_mml();
void ptm_mml_play(string mml, bool loop);
void ptm_mml_beep(float freq, int length);
void ptm_mml_stop();
void ptm_mml_volume(int volume);
