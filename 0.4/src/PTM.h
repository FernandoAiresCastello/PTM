#pragma once
#include <SDL.h>
#include "t_tile.h"
#include "t_string.h"
#include "t_list.h"
#include "t_dict.h"
#include "t_token.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_window.h"
#include "t_program.h"
#include "t_program_line.h"

class PTM
{
public:
	const t_string version_string = "PTM 0.4";
	const t_string title = "PTM - Programmable Tile Machine";

	t_tile tilereg;
	bool auto_screen_update = true;

	void run();
	void exit();
	void halt();
	void reset();
	void pause(int frames);
	void on_machine_cycle();
	void on_escape_key_pressed();
	SDL_Keycode await_keypress();
	void refresh_screen();
	bool is_window_open() const;
	void debug(const t_string& msg);
	void save_program_line(t_program_line& line);
	bool delete_program_line(int line_nr);
	void set_var(const t_string& var, const t_string& value);
	void set_var(const t_string& var, int value);
	const t_string& get_var_str(const t_string& var);
	int get_var_num(const t_string& var);
	const t_dict<t_string, t_string>& get_vars();
	bool has_var(const t_string& var);
	void delete_all_vars();
	t_palette& get_pal();
	t_charset& get_chr();
	t_window& get_wnd();
	t_program& get_prg();
	void run_program();
	void end_program();
	void new_program();
	void save_program(const t_string& filename, bool hex);
	bool load_program(const t_string& filename, bool hex);
	bool has_program_label(const t_string& label);
	void goto_program_label(const t_string& label);
	void call_program_label(const t_string& label);
	bool is_callstack_empty();
	void return_from_call();
	void renumber_program(int interval);
	int get_last_key() const;
	void flush_keyboard();
	bool is_key_pressed(int scancode);
	bool is_key_pressed(const t_string& keyname);
	bool set_function_key(const t_string& keyname, const t_string& value);
	t_list<t_string> list_function_keys();
	t_string input_string(const t_string& prompt, int maxlen);

private:
	bool running = false;
	bool halted = false;
	t_dict<t_string, t_string> vars;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();
};
