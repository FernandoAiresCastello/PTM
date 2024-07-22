#include <Windows.h>
#include <SDL.h>
#include "t_sound.h"
#include "t_dict.h"

t_string t_sound::last_error;

bool sound_loop_thread_running = false;
const int sampling_rate = 44100;
const int buffer_size = 8;
SDL_AudioDeviceID id_device = -1;
Sint16 volume = 256;
float wave_freq = 0;
float sampling_index = 0;
int square_wave_peak = 1;
bool audio_open = false;

static void sound_thread_loop()
{

}

static int sound_thread_loop_start(void* dummy)
{
	sound_loop_thread_running = true;
	while (sound_loop_thread_running)
		sound_thread_loop();

	return 0;
}

static void generate_silence_samples(short* stream, int count)
{
	for (int i = 0; i < count; i++)
		stream[i] = 0;
}

static void generate_square_samples(short* stream, int count)
{
	for (int i = 0; i < count; i++) {
		short value = volume * square_wave_peak;
		stream[i] = value;
		sampling_index += (wave_freq * M_PI * 2) / sampling_index;
		if (sampling_index >= (M_PI * 2)) {
			sampling_index -= M_PI * 2;
			square_wave_peak = -square_wave_peak;
		}
	}
}

static void generate_samples(short* stream, int length)
{
	const int count = length / sizeof(short);

	if (audio_open)
		generate_square_samples(stream, count);
	else
		generate_silence_samples(stream, count);
}

static void fill_audio_buffer_callback(void* userdata, Uint8* ptr_stream, int length)
{
	generate_samples(reinterpret_cast<short*>(ptr_stream), length);
}

void t_sound::init()
{
	SDL_AudioSpec desired, returned;
	SDL_zero(desired);
	desired.freq = sampling_rate;
	desired.format = AUDIO_S16SYS;
	desired.channels = 1;
	desired.samples = buffer_size;
	desired.callback = &fill_audio_buffer_callback;

	id_device = SDL_OpenAudioDevice(nullptr, 0, &desired, &returned, 0);

	if (id_device > 0) {
		SDL_PauseAudioDevice(id_device, 0);
		SDL_CreateThread(sound_thread_loop_start, "ptm_sound_thread_loop", nullptr);
	}
}

// ===== WAV sound file suport =====

struct t_sound_files
{
	t_sound_files();
	~t_sound_files();

	void load(std::string id, std::string file);
	void play(std::string id, bool async);
	bool has(std::string id);
	void stop_all();

private:
	t_dict<std::string, std::string> files; // id -> file_path

	void close_all();
	void set_last_error(unsigned long error);
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
		return;
	}
	files[id] = file;

	std::string openString = "open \"" + file + "\" type waveaudio alias " + id;

	MCIERROR error = mciSendString(openString.c_str(), NULL, 0, NULL);
	if (error) {
		set_last_error(error);
	}
}

void t_sound_files::play(std::string id, bool async)
{
	if (!has(id)) {
		return;
	}

	std::string seekString = "seek " + id + " to start";
	MCIERROR seekError = mciSendString(seekString.c_str(), NULL, 0, NULL);
	if (seekError) {
		set_last_error(seekError);
		return;
	}

	std::string playString = "play " + id;
	if (!async) {
		playString += " wait";
	}
	MCIERROR playError = mciSendString(playString.c_str(), NULL, 0, NULL);
	if (playError) {
		set_last_error(playError);
		return;
	}
}

void t_sound_files::close_all()
{
	for (auto& file : files) {
		std::string closeString = "close " + file.first;
		MCIERROR error = mciSendString(closeString.c_str(), NULL, 0, NULL);
		if (error) {
			set_last_error(error);
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
			set_last_error(playError);
			return;
		}
	}
}

void t_sound_files::set_last_error(unsigned long error)
{
	char msg[1024] = { 0 };
	mciGetErrorString(error, msg, 1024);
	t_sound::last_error = msg;
}

t_sound_files snd_files;

void t_sound::load_wav(const t_string& id, const t_string& filename)
{
	snd_files.load(id, filename);
}

void t_sound::play_wav(const t_string& id)
{
	snd_files.play(id, true);
}

void t_sound::stop_wav()
{
	snd_files.stop_all();
}
