#pragma once
#include "common.h"

struct t_editor_screen {
	int cols;
	int rows;
	t_editor_screen(TBufferedWindow* wnd);
	void clear();
	void set_cursor(int x, int y);
	void move_cursor(int dx, int dy);
	int get_cursor_x();
	int get_cursor_y();
	TTileSeq& get_tile_under_cursor();
	TTileSeq& get_tile_at(int x, int y);
	void set_colors(int fg, int bg, int bdr);
	void draw_border();
	void draw_cursor();
	void print(string text);
	void println(string text);
	void put_char(ixc ch);
	void new_line();
	void scroll_up();
	void scroll_right();
	void scroll_left();
private:
	TBufferedWindow* wnd;
	TTileBuffer* buf;
	struct {
		int x;
		int y;
		TTileSeq tile;
	} csr;
	struct {
		ixp fg;
		ixp bg;
		ixp bdr;
	} color;
};
