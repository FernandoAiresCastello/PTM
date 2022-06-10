#pragma once
#include "common.h"
#include "t_editor_screen_line.h"

struct t_editor_screen {
	struct {
		ixp fg;
		ixp bg;
		ixp bdr;
	} color;
	t_editor_screen(TBufferedWindow* wnd);
	TPalette* palette;
	TCharset* charset;
	void clear_lines();
	void csr_move(int dx, int dy);
	void csr_backspace();
	void csr_delete();
	void csr_home();
	string get_current_line();
	void new_line();
	void type_char(ixc ch, bool overwrite, bool must_update);
	void print(string str, bool overwrite);
	void println(string str, bool overwrite);
private:
	int cols;
	int rows;
	int last_col;
	int last_row;
	std::vector<t_editor_screen_line> lines;
	TBufferedWindow* wnd;
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
	void clear_wbuf();
	void draw_border();
	void draw_lines();
	void draw_line(t_editor_screen_line& line, int ybuf);
};
