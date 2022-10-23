#pragma once
#include "common.h"
#include "t_param.h"
#include "t_layer.h"

struct t_interpreter;
struct t_machine;

struct t_command {
	t_command(t_interpreter* intp);
	bool execute(string& cmd, t_params& args);

private:
	t_interpreter* intp;
	t_machine* machine;

	enum {
		CMP_MODE_EQ, CMP_MODE_NEQ,
		CMP_MODE_GT, CMP_MODE_GTE,
		CMP_MODE_LT, CMP_MODE_LTE,
		CMP_MODE_STR_EQ, CMP_MODE_STR_NEQ
	};
	enum {
		COLOR_R, COLOR_G, COLOR_B
	};

	// Commands
	void nop(t_params& arg);
	void halt(t_params& arg);
	void exit(t_params& arg);
	void reset(t_params& arg);
	void goto_label(t_params& arg);
	void call_label(t_params& arg);
	void return_from_label(t_params& arg);
	void set_variable(t_params& arg);
	void define_constant(t_params& arg);
	void set_cursor_x(t_params& arg);
	void set_cursor_y(t_params& arg);
	void set_cursor_pos(t_params& arg);
	void move_cursor(t_params& arg);
	void move_cursor(t_params& arg, int dx, int dy);
	void init_cur_tile(t_params& arg);
	void append_cur_tile(t_params& arg);
	void set_cur_tile_char(t_params& arg);
	void set_cur_tile_fgcolor(t_params& arg);
	void set_cur_tile_bgcolor(t_params& arg);
	void set_cur_tile_colors(t_params& arg);
	void parse_cur_tile(t_params& arg);
	void store_cur_tile(t_params& arg);
	void load_cur_tile(t_params& arg);
	void set_tile_property(t_params& arg);
	void get_tile_property(t_params& arg);
	void put_tile(t_params& arg);
	void copy_tile(t_params& arg);
	void delete_tile(t_params& arg);
	void put_tile_move_repeat(t_params& arg, int dx, int dy);
	void fill_rect(t_params& arg);
	void fill_layer(t_params& arg);
	void clear_all_layers(t_params& arg);
	void clear_layer(t_params& arg);
	void clear_rect(t_params& arg);
	void draw_tile_sequence(t_params& arg);
	void set_window_bgcolor(t_params& arg);
	void set_tile_transparency(t_params& arg, bool transparent);
	void select_layer(t_params& arg);
	void select_layer(t_params& arg, int layer);
	void define_char_all_bytes(t_params& arg);
	void define_char_single_byte(t_params& arg);
	void define_color(t_params& arg);
	void update_screen(t_params& arg);
	void get_random_number(t_params& arg);
	void pause(t_params& arg);
	void print_text(t_params& arg, bool crlf, bool add_frames);
	void print_text_char(t_params& arg);
	void set_text_fgcolor(t_params& arg);
	void set_text_bgcolor(t_params& arg);
	void set_text_colors(t_params& arg);
	void get_keycode_pressed(t_params& arg);
	void save_debug_file(t_params& arg);
	void show_msgbox(t_params& arg);
	void play_sound(t_params& arg);
	void loop_sound(t_params& arg);
	void set_sound_volume(t_params& arg);
	void stop_sound(t_params& arg);
	void create_array(t_params& arg);
	void array_push(t_params& arg);
	void get_array_length(t_params& arg);
	void set_array_element(t_params& arg);
	void erase_array_element(t_params& arg);
	void clear_array(t_params& arg);
	void copy_array(t_params& arg);
	void increment_variable(t_params& arg);
	void decrement_variable(t_params& arg);
	void math_add(t_params& arg);
	void math_subtract(t_params& arg);
	void math_multiply(t_params& arg);
	void allow_exit_on_escape_key(t_params& arg, bool allow);
	void set_window_title(t_params& arg);
	void get_charset_size(t_params& arg);
	void get_palette_size(t_params& arg);
	void trigger_breakpoint(t_params& arg);
	void play_sound_note(t_params& arg);
	void read_file_into_string(t_params& arg);
	void read_file_into_byte_array(t_params& arg);
	void write_string_to_file(t_params& arg);
	void write_byte_array_to_file(t_params& arg);
	void format_number(t_params& arg);
	void get_cycles(t_params& arg);
	void read_user_input_string(t_params& arg);
	void move_tile(t_params& arg);
	void move_tile_block(t_params& arg);
	void set_viewport(t_params& arg);
	void scroll_viewport(t_params& arg);
	void add_tile_buffer(t_params& arg);
	void show_tile_buffer(t_params& arg, bool visible);
	void select_tile_buffer(t_params& arg);
	void get_buffer_width(t_params& arg);
	void get_buffer_height(t_params& arg);
	void enable_perfmon(t_params& arg);
	void loop_start(t_params& arg);
	void array_loop_start(t_params& arg);
	void loop_end(t_params& arg);
	void loop_break(t_params& arg);
	void loop_continue(t_params& arg);
	void if_block_start(t_params& arg, int cmp_mode);
	void if_block_end(t_params& arg);
	void clear_palette(t_params& arg);
	void get_palette_color(t_params& arg);
	void get_palette_color_comp(t_params& arg, int comp);
	void set_palette_color_comp(t_params& arg, int comp);
	void get_charset_binary_string(t_params& arg);
	void set_charset_binary_string(t_params& arg);
	void get_substring(t_params& arg);
	void get_string_length(t_params& arg);
	void repeat_string(t_params& arg);
	void concatenate_strings(t_params& arg);
	void split_string(t_params& arg);
	void trim_string(t_params& arg);
	void uppercase_string(t_params& arg);
	void lowercase_string(t_params& arg);
	void replace_string(t_params& arg);
	void get_string_char_at(t_params& arg);
	void get_string_index_of_char(t_params& arg);
	void string_starts_with(t_params& arg);
	void string_ends_with(t_params& arg);
	void string_contains(t_params& arg);
};
