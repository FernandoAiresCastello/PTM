#pragma once
#include "common.h"
#include "t_program.h"
#include "t_ui_base.h"
#include "t_layer.h"

struct t_config;

enum class t_confirm_result {
	cancel = -1, no = 0, yes = 1
};
struct t_program_editor : public t_ui_base {
	t_program_editor(t_globals* g);
	~t_program_editor();
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
		const int layer = 1;
		int x = 1;
		int y = 1;
		TTileSeq tile;
	} scr_csr;
	struct {
		int first_line_ix = 0;
		int first_char_ix = 0;
		int max_lines = 0;
		int max_chars = 0;
		int layer = t_layer::bottom;
	} prg_view;
	int line_selection_start = -1;
	std::vector<string> clipboard;
	bool unsaved = false;

	void on_run_loop();
	bool on_exit();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void on_mouse_wheel(int dist_y);
	void draw();
	void draw_border_info();
	void draw_program();
	void apply_syntax_coloring();
	void draw_cursor();
	void hide_cursor();
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
	void add_empty_line();
	void type_char(int ch);
	void type_crlf();
	void type_backspace();
	void type_delete();
	void type_pgup();
	void type_pgdn();
	void new_program();
	void reload_program();
	void load_program();
	void load_program(string file);
	void save_program(string file);
	void save_program_as();
	void compile_and_run();
	void print_errors(std::vector<string>& errors);
	void print(string text, int x, int y);
	void copy_lines(bool cancel_selection);
	void cut_lines();
	void paste_lines();
	void clear_current_line();
	void clear_lines();
	void delete_lines();
	void start_line_selection();
	void cancel_line_selection();
	std::pair<int, int> get_line_selection_range();
	bool is_selected(int line_ix);
	bool has_selection();
	void show_help();
	t_confirm_result confirm(string msg);
	void alert_error(string title, string text);
	void beep();
};
