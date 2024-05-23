#pragma once
#include "t_tilebuffer.h"
#include "t_window.h"

class t_charset;
class t_palette;

class t_screen
{
public:
	t_screen();

	void draw(t_window* wnd, t_charset* chr, t_palette* pal);

private:
	t_tilebuffer buf = t_tilebuffer(t_window::cols, t_window::rows);
};
