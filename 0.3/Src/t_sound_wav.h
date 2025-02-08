#pragma once
#include "t_dict.h"
#include "t_string.h"

class t_sound_wav
{
public:
	t_sound_wav();
	~t_sound_wav();

	void load_wav(const t_string& id, const t_string& filename);
	void play_wav(const t_string& id);
	void stop_wav();
	const t_string& get_error();

private:
	t_dict<t_string, t_string> files; // id -> file_path
	t_string error;

	void load(const t_string& id, const t_string& file);
	void play(const t_string& id, bool async);
	bool has(const t_string& id) const;
	void stop_all();
	void close_all();
	void set_error(unsigned long error);
};
