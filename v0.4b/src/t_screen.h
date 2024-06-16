#pragma once
#include <memory>
#include "t_window.h"
#include "t_index.h"

class t_charset;
class t_palette;
class t_tilebuffer;

class t_screen
{
public:
	t_screen();
	~t_screen() = default;

	void set_window(t_window* wnd);
	void set_charset(t_charset* chr);
	void set_palette(t_palette* pal);
	void draw();
	void color(t_index fgc);
	void color(t_index fgc, t_index bgc);
	void color(t_index fgc, t_index bgc, t_index bdrc);
	void put(const t_tile& tile, int x, int y);
	void print(const t_string& str, int x, int y);

private:
	t_window* wnd = nullptr;
	t_charset* chr = nullptr;
	t_palette* pal = nullptr;
	std::unique_ptr<t_tilebuffer> buf_bdr;
	std::unique_ptr<t_tilebuffer> buf;
	t_index fore_color = 15;
	t_index back_color = 1;
	t_index border_color = 10;

	void update_monochrome_tiles();
};