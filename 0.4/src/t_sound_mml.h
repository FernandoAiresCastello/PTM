#pragma once
#include "t_string.h"

class t_sound_mml
{
public:
	static const int max_volume = 127;

	t_sound_mml();
	~t_sound_mml();

	void set_volume(int volume);
	void beep(double frequency, int duration);
	void play_note(const t_string& note, int duration);
};
