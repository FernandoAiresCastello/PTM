#pragma once
#include "t_string.h"

class t_sound
{
public:
	static t_string last_error;

	void init();
	void load_wav(const t_string& id, const t_string& filename);
	void play_wav(const t_string& id);
	void stop_wav();
};
