#pragma once
#include "t_string.h"

class t_sound_wav
{
public:
	void play(const t_string& filename, bool loop);
	void stop();
};
