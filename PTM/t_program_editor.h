#pragma once
#include "common.h"
#include "t_program.h"

struct t_config;
struct t_editor_screen;

struct t_program_editor {
	bool exit_requested;
	t_program_editor(TBufferedWindow* wnd, TSound* snd, t_config* cfg);
	~t_program_editor();
	void print_intro();
	void print_debug();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
private:
	t_program prg;
	t_editor_screen* scr;
	TSound* snd;
	void print_ok();
	void print_msg(string msg);
	void print_error(string error);
	void print_program_line(t_source_line* line);
	void process_line(string line);
	void execute_command(string line);
	bool assert_color_ix(int ix);
	bool assert_argc(std::vector<string>& args, int argc);
	void store_program_line(string line);
};
