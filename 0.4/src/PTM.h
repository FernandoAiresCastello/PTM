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
#include "t_table.h"
#include "t_namespace.h"
#include "t_pointers.h"
#include "t_sprite.h"
#include "t_sound.h"
#include "t_screen.h"
#include "t_array_ref.h"
#include "t_user_tilebuffer.h"

class PTM
{
public:
	const t_string title = "PTM - Programmable Tile Machine";
	
	const t_string version_string	= "PTM 0.4";
	const t_string title_short		= "Programmable Tile Machine";
	const t_string copyright_notice	= "` 2023-2024 by F.A.Castello";

	const t_string autoexec_file = "AUTORUN";
	const t_string autosave_file = "AUTOSAVE";

	t_tile tilereg;
	bool auto_screen_update = true;
	bool enable_user_break = true;
	t_user_tilebuffer usr_tilebuf;
	bool usr_tilebuf_selected = false;

	void run();
	void exit();
	void halt();
	void reset();
	void pause(int frames);
	void on_machine_cycle();
	void on_escape_key_pressed();
	void on_exit();
	SDL_Keycode await_keypress();
	void refresh_screen();
	bool is_window_open() const;
	void debug(const t_string& msg);
	void save_program_line(t_program_line& line);
	bool delete_program_line(int line_nr);

	void set_var(const t_param& param, int value, t_string& out_error);
	void set_var(const t_param& param, const t_string& value, t_string& out_error);
	int get_var_num(const t_param& param, t_string& out_error);
	int get_var_num(const t_string& varname);
	const t_string& get_var_str(const t_param& param, t_string& out_error);
	const t_string& get_var_str(const t_string& varname);

	const t_namespace<t_string>& get_vars();
	bool has_var(const t_string& var);
	bool has_array(const t_string& var);
	void create_array(const t_array_ref& array_ref, t_string& out_error);
	const t_string& get_array_element(const t_array_ref& ref, t_string& out_error);
	int get_array_length(const t_string& array_name, t_string& out_error);
	void delete_all_vars();

	static t_palette& get_pal();
	static t_charset& get_chr();
	static t_screen& get_screen();
	t_window& get_wnd();
	t_program& get_prg();
	void run_program_from_immediate_mode();
	void run_program_from_another_program();
	bool has_new_program_loaded_at_runtime();
	void end_program();
	void on_program_end();
	void new_program();
	void save_program(const t_string& filename);
	bool load_program(const t_string& filename);
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
	t_string input_string(const t_string& prompt, int maxlen);
	void autosave_program_file();
	int find_program_label(const t_string& label);
	t_sound& get_sound();
	const t_string& get_last_program_filename() const;
	void draw_user_buffer(int x, int y, int w, int h, int xoff, int yoff);

private:
	bool running = false;
	bool halted = false;

	t_namespace<t_string> vars;
	t_namespace<t_list<t_string>> arrays;
	t_string last_program_filename;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();

	void set_array(const t_array_ref& ref, const t_string& value, t_string& out_error);
};
