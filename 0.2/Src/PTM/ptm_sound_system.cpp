#include <Windows.h>
#include "ptm_sound_system.h"

struct t_sound_files
{
	t_sound_files();
	~t_sound_files();

	void load(std::string id, std::string file);
	void play(std::string id, bool async);
	bool has(std::string id);
	void stop_all();

private:
	std::unordered_map<std::string, std::string> files; // id -> file_path

	void close_all();
	void show_error(unsigned long error);
};
t_sound_files::t_sound_files()
{
}
t_sound_files::~t_sound_files()
{
	close_all();
}
void t_sound_files::load(std::string id, std::string file)
{
	if (has(id)) {
		MsgBox::Error("Sound file is already loaded\r\n\r\n"
			"Sound ID: " + id + "\r\n"
			"File: " + file);
		return;
	}
	files[id] = file;

	std::string openString = "open \"" + file + "\" type waveaudio alias " + id;

	MCIERROR error = mciSendString(openString.c_str(), NULL, 0, NULL);
	if (error) {
		show_error(error);
	}
}
void t_sound_files::play(std::string id, bool async)
{
	if (!has(id)) {
		MsgBox::Error("Sound not found with ID: " + id);
		return;
	}

	std::string seekString = "seek " + id + " to start";
	MCIERROR seekError = mciSendString(seekString.c_str(), NULL, 0, NULL);
	if (seekError) {
		show_error(seekError);
		return;
	}

	std::string playString = "play " + id;
	if (!async) {
		playString += " wait";
	}
	MCIERROR playError = mciSendString(playString.c_str(), NULL, 0, NULL);
	if (playError) {
		show_error(playError);
		return;
	}
}
void t_sound_files::close_all()
{
	for (auto& file : files) {
		std::string closeString = "close " + file.first;
		MCIERROR error = mciSendString(closeString.c_str(), NULL, 0, NULL);
		if (error) {
			show_error(error);
		}
	}
	files.clear();
}
bool t_sound_files::has(std::string id)
{
	return files.find(id) != files.end();
}
void t_sound_files::stop_all()
{
	for (auto& file : files) {
		std::string playString = "stop " + file.first;
		MCIERROR playError = mciSendString(playString.c_str(), NULL, 0, NULL);
		if (playError) {
			show_error(playError);
			return;
		}
	}
}
void t_sound_files::show_error(unsigned long error)
{
	char msg[1024] = { 0 };
	mciGetErrorString(error, msg, 1024);
	MsgBox::Error(msg);
}

t_sound_files snd_files;

bool ptm_load_sound_wav(string id, string file)
{
	if (File::Exists(file)) {
		snd_files.load(id, file);
	}
	else {
		return false;
	}
	return true;
}
bool ptm_play_sound_wav(string id)
{
	if (snd_files.has(id)) {
		snd_files.play(id, true);
		return true;
	}
	else {
		return false;
	}
}
void ptm_stop_all_sounds()
{
	snd_files.stop_all();
}
