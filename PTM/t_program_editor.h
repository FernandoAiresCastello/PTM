#pragma once
#include "common.h"
#include "t_program.h"

struct t_config;

struct t_program_editor {
	t_program_editor(TBufferedWindow* wnd, t_config* cfg);
	void run();
private:
	TBufferedWindow* wnd;
	TTileBuffer* buf;
	bool running;
	t_program prg;
	bool csr_overwrite;
	struct {
		int fg = 15;
		int bg = 0;
		int bdr_fg = 15;
		int bdr_bg = 5;
	} color;
	struct {
		int line_ix = 0;
		int char_ix = 0;
	} prg_csr;
	struct {
		int x = 1;
		int y = 1;
		TTileSeq tile;
	} scr_csr;
	struct {
		int first_line_ix = 0;
		int first_char_ix = 0;
		int max_lines = 0;
		int max_chars = 0;
	} prg_view;
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void draw_border();
	void draw_program();
	void draw_cursor();
	string* get_current_line();
	string* get_line_below();
	int get_char_under_cursor();
	void move_prg_csr_right();
	void move_prg_csr_left();
	void move_prg_csr_down();
	void move_prg_csr_up();
	void move_prg_csr_end_x();
	void move_prg_csr_home_x();
	void move_prg_csr_home();
	void move_prg_csr_end();
	bool is_valid_prg_char(int ch);
	void type_char(int ch);
	void type_crlf();
	void type_backspace();
	void type_delete();
};
