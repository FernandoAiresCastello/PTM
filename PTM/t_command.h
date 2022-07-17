#pragma once
#include "common.h"
#include "t_param.h"

struct t_interpreter;
struct t_machine;

struct t_command {
	t_command(t_interpreter* intp);
	bool execute(string& cmd, t_params& args);
private:
	t_interpreter* intp;
	t_machine* machine;
	std::vector<string> get_debug_info();
	void halt(t_params& arg);
	void exit(t_params& arg);
	void goto_label(t_params& arg);
	void call_label(t_params& arg);
	void return_from_label(t_params& arg);
	void set_variable(t_params& arg);
	void define_constant(t_params& arg);
	void set_cursor_pos(t_params& arg);
	void move_cursor(t_params& arg);
	void init_cur_tile(t_params& arg);
	void append_cur_tile(t_params& arg);
	void set_cur_tile_char(t_params& arg);
	void set_cur_tile_fgcolor(t_params& arg);
	void set_cur_tile_bgcolor(t_params& arg);
	void parse_cur_tile(t_params& arg);
	void store_cur_tile(t_params& arg);
	void parse_and_store_tile(t_params& arg);
	void load_cur_tile(t_params& arg);
	void put_tile(t_params& arg);
	void put_tile_repeat_right(t_params& arg);
	void put_tile_repeat_left(t_params& arg);
	void put_tile_repeat_up(t_params& arg);
	void put_tile_repeat_down(t_params& arg);
	void fill_rect(t_params& arg);
	void clear_all_layers(t_params& arg);
	void clear_layer(t_params& arg);
	void clear_rect(t_params& arg);
	void set_wnd_bgcolor(t_params& arg);
	void set_tile_transparency(t_params& arg);
	void select_layer(t_params& arg);
	void define_char(t_params& arg);
	void define_color(t_params& arg);
	void update_screen(t_params& arg);
	void get_random_number(t_params& arg);
	void pause(t_params& arg);
	void create_obj(t_params& arg);
	void set_obj_prop(t_params& arg);
	void set_obj_tile(t_params& arg);
	void print_text(t_params& arg);
	void set_text_fgcolor(t_params& arg);
	void set_text_bgcolor(t_params& arg);
	void set_text_colors(t_params& arg);
	void draw_obj(t_params& arg);
	void get_key_pressed(t_params& arg);
	void call_if_key_pressed(t_params& arg);
	void save_debug_file(t_params& arg);
};
