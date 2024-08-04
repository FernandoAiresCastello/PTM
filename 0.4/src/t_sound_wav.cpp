#include <Windows.h>
#include "t_sound_wav.h"
#include "t_dict.h"

t_sound_wav::t_sound_wav()
{
}

t_sound_wav::~t_sound_wav()
{
	close_all();
}

void t_sound_wav::load_wav(const t_string& id, const t_string& filename)
{
	load(id, filename);
}

void t_sound_wav::play_wav(const t_string& id)
{
	play(id, true);
}

void t_sound_wav::stop_wav()
{
	stop_all();
}

const t_string& t_sound_wav::get_last_error()
{
	return last_error;
}

void t_sound_wav::load(const t_string& id, const t_string& file)
{
	if (has(id))
		return;
	
	files[id] = file;

	std::string openString = "open \"" + file.s_str() + "\" type waveaudio alias " + id.s_str();

	MCIERROR error = mciSendString(openString.c_str(), NULL, 0, NULL);
	if (error)
		set_last_error(error);
}

void t_sound_wav::play(const t_string& id, bool async)
{
	if (!has(id))
		return;

	std::string seekString = "seek " + id.s_str() + " to start";
	MCIERROR seekError = mciSendString(seekString.c_str(), NULL, 0, NULL);
	if (seekError) {
		set_last_error(seekError);
		return;
	}

	std::string playString = "play " + id.s_str();
	if (!async)
		playString += " wait";
	
	MCIERROR playError = mciSendString(playString.c_str(), NULL, 0, NULL);
	if (playError) {
		set_last_error(playError);
		return;
	}
}

void t_sound_wav::close_all()
{
	for (auto& file : files) {
		std::string closeString = "close " + file.first.s_str();
		MCIERROR error = mciSendString(closeString.c_str(), NULL, 0, NULL);
		if (error)
			set_last_error(error);
	}
	files.clear();
}

bool t_sound_wav::has(const t_string& id) const
{
	return files.find(id) != files.end();
}

void t_sound_wav::stop_all()
{
	for (auto& file : files) {
		std::string playString = "stop " + file.first.s_str();
		MCIERROR playError = mciSendString(playString.c_str(), NULL, 0, NULL);
		if (playError) {
			set_last_error(playError);
			return;
		}
	}
}

void t_sound_wav::set_last_error(unsigned long error)
{
	char msg[1024] = { 0 };
	mciGetErrorString(error, msg, 1024);
	t_sound_wav::last_error = msg;
}
