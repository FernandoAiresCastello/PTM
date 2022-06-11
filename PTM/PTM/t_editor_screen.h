#pragma once
#include "common.h"
#include "t_editor_screen_line.h"

struct t_editor_screen {
	TBufferedWindow* wnd;
	struct {
		ixp fg;
		ixp bg;
		ixp bdr;
	} color;
	t_editor_screen(TBufferedWindow* wnd);
	TPalette* palette;
	TCharset* charset;
	void clear_lines();
	void clear_current_line();
	void csr_move(int dx, int dy);
	void csr_backspace();
	void csr_delete();
	void csr_home();
	void csr_line_start();
	void csr_line_end();
	void csr_end();
	int csr_x();
	int csr_y();
	void crlf();
	t_editor_screen_line& get_current_line();
	string get_current_string();
	void type_char(TTileSeq tile, bool overwrite, bool must_update);
	void type_tile(TTileSeq tile, bool overwrite, bool must_update);
	void type_char(ixc ch, bool overwrite, bool must_update);
	void print(string str, bool overwrite);
	void println(string str, bool overwrite);
	void print_debug(string str);
	int line_count();
	bool is_cursor_on_last_line();
	void scroll_right();
	void scroll_left();
	void scroll_up();
	void scroll_down();
private:
	int cols;
	int rows;
	int last_col;
	int last_row;
	std::vector<t_editor_screen_line> lines;
	TTileBuffer* wnd_buf;
	struct {
		int x;
		int y;
		TTileSeq tile;
	} csr;
	int first_line_ix;
	int first_char_ix;
	int max_visible_lines;
	int max_visible_chars;
	
	void update();
	void new_line();
	void next_line();
	void clear_wbuf();
	void draw_border();
	void draw_lines();
	void draw_line(t_editor_screen_line& line, int ybuf);
	void draw_cursor();
	ixc get_char_at_cursor();
};
