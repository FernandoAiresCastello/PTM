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
	void play_mml(const t_string& mml);
	void play_mml_loop(const t_string& mml);

private:
	friend int play_mml_threaded(void* mml_ptr);
	friend int play_mml_loop_threaded(void* mml_ptr);

	void play_note(const t_string& note, int duration);
};
