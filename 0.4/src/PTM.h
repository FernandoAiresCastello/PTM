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
#include "t_sound_mml.h"
#include "t_screen.h"

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
	void set_var(const t_string& var, const t_string& value);
	void set_var(const t_string& var, int value);
	const t_string& get_var_str(const t_string& var);
	int get_var_num(const t_string& var);
	const t_namespace<t_string>& get_vars();
	bool has_var(const t_string& var);
	void delete_all_vars();
	void delete_all_tables();
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
	void add_sprite(const t_string& name, int x, int y, bool visible);
	t_sprite_ptr get_sprite(const t_string& name);
	void delete_all_sprites();
	const t_string& get_last_program_filename() const;
	void autosave_program_file();
	void create_table(const t_string& name, int cols, int rows);
	bool has_table(const t_string& name);
	t_table& get_table(const t_string& name);
	const t_namespace<t_table>& get_tables();
	void save_tilereg(const t_string& name);
	void load_tilereg(const t_string& name);
	bool has_tilereg(const t_string& name);
	int find_program_label(const t_string& label);
	t_sound_mml& get_sound_gen();

private:
	bool running = false;
	bool halted = false;

	t_string last_program_filename;
	t_namespace<t_string> vars;
	t_namespace<t_sprite_ptr> sprites;
	t_namespace<t_table> tables;
	t_namespace<t_tile> tile_presets;
	t_sound_mml sound_gen;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();
};
