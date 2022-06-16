#pragma once
#include "common.h"
#include "t_program.h"
#include "t_ui_base.h"

struct t_config;

struct t_program_editor : public t_ui_base {
	t_program_editor(t_globals* g);
private:
	t_program prg;
	string prg_filename;
	bool csr_overwrite;
	bool info_visible;
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
	void on_run_loop();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void draw_border_info();
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
	void type_pgup();
	void type_pgdn();
	void load_program(string file);
	void compile_and_run();
	void print_errors(std::vector<string>& errors);
	void print(string text, int x, int y);
};
