#pragma once
#include <memory>
#include "t_tile.h"

class t_window;
class t_charset;
class t_palette;

class t_tilebuffer
{
public:
	const int cols;
	const int rows;

	t_tilebuffer();
	t_tilebuffer(int cols, int rows);
	~t_tilebuffer() = default;

	int last_row() const;
	int last_col() const;
	void draw(t_window* wnd, t_charset* chr, t_palette* pal);
	void draw(t_window* wnd, t_charset* chr, t_palette* pal, int px, int py);
	void set(const t_tile& tile, int x, int y);
	void set_text(const t_string& text, int x, int y, t_index fgc, t_index bgc, t_tileflags flags = t_tileflags());
	int set_text_wrap(const t_string& text, int* xptr, int* yptr, t_index fgc, t_index bgc, t_tileflags flags = t_tileflags());
	void set_blank(int x, int y);
	t_tile& get_ref(int x, int y);
	t_tile get_copy(int x, int y) const;
	void fill(const t_tile& tile);
	void clear();

private:
	const int length;

	t_list<t_tile> tiles;

	void draw_tile(t_tile& tile, t_window* wnd, t_charset* chr, t_palette* pal, int x, int y) const;
};
