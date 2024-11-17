#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <map>
#include "t_sound.h"
#include "t_string.h"

bool sound_system_running = true;

// Constants for 8-bit audio
const int SAMPLE_RATE = 44100;
const int SAMPLES_PER_MILLISECOND = SAMPLE_RATE / 1000;
const int CHANNELS = 1;

// Simple frequencies for notes
const std::map<std::string, double> freq_tbl = {
    {"C0", 16.35},
    {"C#0", 17.32},
    {"D0", 18.35},
    {"D#0", 19.45},
    {"E0", 20.6},
    {"F0", 21.83},
    {"F#0", 23.12},
    {"G0", 24.5},
    {"G#0", 25.96},
    {"A0", 27.5},
    {"A#0", 29.14},
    {"B0", 30.87},
    {"C1", 32.7},
    {"C#1", 34.65},
    {"D1", 36.71},
    {"D#1", 38.89},
    {"E1", 41.2},
    {"F1", 43.65},
    {"F#1", 46.25},
    {"G1", 49},
    {"G#1", 51.91},
    {"A1", 55},
    {"A#1", 58.27},
    {"B1", 61.74},
    {"C2", 65.41},
    {"C#2", 69.3},
    {"D2", 73.42},
    {"D#2", 77.78},
    {"E2", 82.41},
    {"F2", 87.31},
    {"F#2", 92.5},
    {"G2", 98},
    {"G#2", 103.83},
    {"A2", 110},
    {"A#2", 116.54},
    {"B2", 123.47},
    {"C3", 130.81},
    {"C#3", 138.59},
    {"D3", 146.83},
    {"D#3", 155.56},
    {"E3", 164.81},
    {"F3", 174.61},
    {"F#3", 185},
    {"G3", 196},
    {"G#3", 207.65},
    {"A3", 220},
    {"A#3", 233.08},
    {"B3", 246.94},
    {"C4", 261.63},
    {"C#4", 277.18},
    {"D4", 293.66},
    {"D#4", 311.13},
    {"E4", 329.63},
    {"F4", 349.23},
    {"F#4", 369.99},
    {"G4", 392},
    {"G#4", 415.3},
    {"A4", 440},
    {"A#4", 466.16},
    {"B4", 493.88},
    {"C5", 523.25},
    {"C#5", 554.37},
    {"D5", 587.33},
    {"D#5", 622.25},
    {"E5", 659.25},
    {"F5", 698.46},
    {"F#5", 739.99},
    {"G5", 783.99},
    {"G#5", 830.61},
    {"A5", 880},
    {"A#5", 932.33},
    {"B5", 987.77},
    {"C6", 1046.5},
    {"C#6", 1108.73},
    {"D6", 1174.66},
    {"D#6", 1244.51},
    {"E6", 1318.51},
    {"F6", 1396.91},
    {"F#6", 1479.98},
    {"G6", 1567.98},
    {"G#6", 1661.22},
    {"A6", 1760},
    {"A#6", 1864.66},
    {"B6", 1975.53},
    {"C7", 2093},
    {"C#7", 2217.46},
    {"D7", 2349.32},
    {"D#7", 2489.02},
    {"E7", 2637.02},
    {"F7", 2793.83},
    {"F#7", 2959.96},
    {"G7", 3135.96},
    {"G#7", 3322.44},
    {"A7", 3520},
    {"A#7", 3729.31},
    {"B7", 3951.07},
    {"C8", 4186.01},
    {"C#8", 4434.92},
    {"D8", 4698.63},
    {"D#8", 4978.03},
    {"E8", 5274.04},
    {"F8", 5587.65},
    {"F#8", 5919.91},
    {"G8", 6271.93},
    {"G#8", 6644.88},
    {"A8", 7040},
    {"A#8", 7458.62},
    {"B8", 7902.13}
};

// Global variables
std::mutex audioMutex;
double currentFrequency = 0.0;  // 0.0 means silence
std::atomic<int> currentVolume(t_sound::max_volume);  // Default volume is max (atomic for thread safety)
std::atomic<int> remainingSamples(0);  // Tracks remaining samples for the current note

// Audio generation callback
static void audioCallback(void* userdata, Uint8* stream, int len) {
    static double phase = 0.0;
    int sample_count = len / sizeof(Uint8);

    audioMutex.lock();
    double frequency = currentFrequency;  // Copy current frequency
    int samplesLeft = remainingSamples.load();
    audioMutex.unlock();

    if (frequency == 0.0 || samplesLeft <= 0) {
        // Generate silence
        std::memset(stream, 128, len);  // 128 is silence for 8-bit audio
    }
    else {
        int volume = currentVolume.load();  // Load volume atomically
        for (int i = 0; i < sample_count && samplesLeft > 0; i++, samplesLeft--) {
            stream[i] = (Uint8)(volume * (std::sin(phase * 2 * M_PI) > 0 ? 1 : -1) + 128);  // Square wave
            phase += frequency / SAMPLE_RATE;
            if (phase >= 1.0) phase -= 1.0;
        }
        // Update the remaining samples
        remainingSamples.store(samplesLeft);
    }
}

static void muteCurrentFrequency() {
    // Set frequency to 0 to stop the sound (silence)
    audioMutex.lock();
    currentFrequency = 0.0;
    remainingSamples.store(0);
    audioMutex.unlock();
}

static void playFrequencyWithDuration(double frequency, int durationMs) {
    // Update the frequency and remaining samples in a thread-safe way
    audioMutex.lock();
    currentFrequency = frequency;
    remainingSamples.store(durationMs * SAMPLES_PER_MILLISECOND);
    audioMutex.unlock();
}

static void setVolume(int volume) {
    // Clamp volume to the 0 to MAX_AMPLITUDE range
    if (volume < 0) volume = 0;
    if (volume > t_sound::max_volume) volume = t_sound::max_volume;
    currentVolume.store(volume);  // Atomically set volume
}

//=============================================================================
//      T_SOUND_MML
//=============================================================================

t_sound::t_sound()
{
    // Set up the audio specification
    SDL_AudioSpec audioSpec;
    SDL_zero(audioSpec);
    audioSpec.freq = SAMPLE_RATE;
    audioSpec.format = AUDIO_U8;
    audioSpec.channels = CHANNELS;
    audioSpec.samples = 512;
    audioSpec.callback = audioCallback;

    // Open the audio device
    if (SDL_OpenAudio(&audioSpec, nullptr) < 0)
        throw t_string::fmt("Failed to open audio: %s", SDL_GetError());

    SDL_PauseAudio(0);  // Start the audio stream
}

t_sound::~t_sound()
{
    sound_system_running = false;
    SDL_CloseAudio();
}

void t_sound::set_volume(int volume)
{
    // Volume should be between 0 and MAX_AMPLITUDE
    if (volume < 0) volume = 0;
    if (volume > t_sound::max_volume) volume = t_sound::max_volume;

    audioMutex.lock();
    currentVolume = volume;
    audioMutex.unlock();
}

struct t_beep {
    double frequency = 0.0;
    int duration = 0;
};
t_list<t_beep> beep_seq;
SDL_Thread* beep_thread = nullptr;

static int beep_threaded(void* dummy)
{
    while (sound_system_running) {
        if (beep_seq.empty())
            continue;

        auto&& b = beep_seq.back();
        beep_seq.pop_back();
        playFrequencyWithDuration(b.frequency, b.duration);
        SDL_Delay(b.duration);
    }
    return 0;
}

void t_sound::beep(double frequency, int duration)
{
    t_beep b;
    b.frequency = frequency;
    b.duration = duration;
    beep_seq.push_back(b);

    if (!beep_thread)
        beep_thread = SDL_CreateThread(beep_threaded, "PTM_BeepSeq_Thread", nullptr);
}

void t_sound::alert()
{
    beep(1450, 50);
}

void t_sound::keystroke()
{
    beep(70, 5);
}

// ===== MML =====

void t_sound::play_note(const t_string& note, int duration)
{
    if (freq_tbl.contains(note))
        playFrequencyWithDuration(freq_tbl.at(note), duration);
}

struct {
    t_sound* snd = nullptr;
    int min_note_duration = 0;
    int max_note_duration = 1000;

    // ONE-SHOT
    struct {
        t_string mml = "";
        int duration = 100;
        const int delay_between_notes = 20;
        int thread_count = 0;
        const int max_thread_count = 3;
        void pop_thread() {
            thread_count--;
            if (thread_count < 0)
                thread_count = 0;
        }
    } one_shot;

    // LOOPED
    struct {
        t_string mml = "";
        int duration = 100;
        const int delay_between_notes = 20;
        int thread_count = 0;
        const int max_thread_count = 1;
        bool stop = false;
        void pop_thread() {
            thread_count--;
            if (thread_count < 0)
                thread_count = 0;
        }
    } looped;

} mml_thread_params;

static void play_mml_common(bool loop)
{
    auto&& mml = loop ? mml_thread_params.looped.mml : mml_thread_params.one_shot.mml;

    for (auto&& note : mml.to_upper().split(' ', true)) {
        if (note[0] == 'L') {
            if (note.length() >= 2) {
                int duration = std::clamp(note.skip(1).to_int(), 
                    mml_thread_params.min_note_duration, mml_thread_params.max_note_duration);

                if (loop)
                    mml_thread_params.looped.duration = duration;
                else
                    mml_thread_params.one_shot.duration = duration;
            }
        }
        else if (note[0] == 'P') {
            if (note.length() >= 2) {
                int duration = std::clamp(note.skip(1).to_int(),
                    mml_thread_params.min_note_duration, mml_thread_params.max_note_duration);

                SDL_Delay(duration);
            }
        }
        else {
            if (loop) {
                mml_thread_params.snd->play_note(note, mml_thread_params.looped.duration);
                SDL_Delay(mml_thread_params.looped.duration + mml_thread_params.looped.delay_between_notes);
            }
            else {
                mml_thread_params.snd->play_note(note, mml_thread_params.one_shot.duration);
                SDL_Delay(mml_thread_params.one_shot.duration + mml_thread_params.one_shot.delay_between_notes);
            }
        }
    }
}

// ===== THREADED MML - ONE-SHOT =====

static int play_mml_threaded(void* dummy)
{
    play_mml_common(false);
    mml_thread_params.one_shot.pop_thread();

    return 0;
}

void t_sound::play_mml(const t_string& mml)
{
    if (mml_thread_params.one_shot.thread_count >= mml_thread_params.one_shot.max_thread_count)
        return;

    mml_thread_params.snd = this;
    mml_thread_params.one_shot.mml = mml;
    mml_thread_params.one_shot.thread_count++;

    SDL_Thread* thread = SDL_CreateThread(play_mml_threaded, "PTM_MML_Thread", nullptr);
}

// ===== THREADED MML - LOOP =====

static int play_mml_loop_threaded(void* dummy)
{
    while (!mml_thread_params.looped.stop)
        play_mml_common(true);

    mml_thread_params.looped.pop_thread();

    return 0;
}

void t_sound::play_mml_loop(const t_string& mml)
{
    if (mml.trim().empty()) {
        mml_thread_params.looped.stop = true;
        return;
    }
    if (mml_thread_params.looped.thread_count >= mml_thread_params.looped.max_thread_count) {
        return;
    }

    mml_thread_params.snd = this;
    mml_thread_params.looped.mml = mml;
    mml_thread_params.looped.thread_count++;
    mml_thread_params.looped.stop = false;

    SDL_Thread* thread = SDL_CreateThread(play_mml_loop_threaded, "PTM_MML_LOOP_Thread", nullptr);
}
