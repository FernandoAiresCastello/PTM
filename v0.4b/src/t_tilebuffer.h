#pragma once
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
	~t_tilebuffer();

	void draw(t_window* wnd, t_charset* chr, t_palette* pal);
	void draw(t_window* wnd, t_charset* chr, t_palette* pal, int px, int py);
	void set(t_tile tile, int x, int y);
	void set_text(t_string text, int x, int y, t_index fgc, t_index bgc);
	t_tile& get_ref(int x, int y);
	t_tile get_copy(int x, int y) const;
	void fill(t_tile tile);
	void clear();	

private:
	const int length;

	t_tile* tiles = nullptr;
};
