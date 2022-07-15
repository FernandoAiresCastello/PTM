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
	void halt(t_params& arg);
	void exit(t_params& arg);
	void branch(t_params& arg);
	void set_variable(t_params& arg);
	void create_view(t_params& arg);
	void select_view(t_params& arg);
	void unselect_view(t_params& arg);
	void set_cursor_pos(t_params& arg);
	void move_cursor(t_params& arg);
	void append_cur_tile(t_params& arg);
	void clear_cur_tile(t_params& arg);
	void put_tile(t_params& arg);
	void fill_view(t_params& arg);
	void clear_all_layers(t_params& arg);
	void clear_view(t_params& arg);
	void set_wnd_bgcolor(t_params& arg);
	void set_tile_transparency(t_params& arg);
	void select_layer(t_params& arg);
	void define_char(t_params& arg);
	void define_color(t_params& arg);
	void update_screen(t_params& arg);
};
