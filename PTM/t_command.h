#pragma once
#include "common.h"
#include "t_param.h"

struct t_interpreter;
struct t_game;

struct t_command {
	t_command(t_interpreter* intp);
	void halt(t_params& arg);
	void exit(t_params& arg);
	void set_wnd_bgcolor(t_params& arg);
	void set_text_fgcolor(t_params& arg);
	void set_text_bgcolor(t_params& arg);
	void set_text_colors(t_params& arg);
	void clear_screen(t_params& arg);
	void update_screen(t_params& arg);
	void print_text(t_params& arg);
	void print_char(t_params& arg);
	void set_text_cursor_pos(t_params& arg);
	void add_tile(t_params& arg);
	void delete_tile(t_params& arg);
	void branch(t_params& arg);
	void define_alias(t_params& arg);
	void poke(t_params& arg);
	void poke_string(t_params& arg);
private:
	t_interpreter* intp;
	t_game* game;
};
