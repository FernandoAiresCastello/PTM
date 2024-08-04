#include <SDL.h>
#include "t_sound_gen.h"
#include "t_dict.h"

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

void t_sound_gen::init()
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
		SDL_CreateThread(sound_thread_loop_start, "ptm_sound_gen_thread", nullptr);
	}
}
