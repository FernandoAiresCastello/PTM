#pragma once
#include "global.h"
#include "t_index.h"
#include "t_color.h"

class t_main_window;
class t_image;
class t_charset;

class t_screen
{
public:
	t_main_window* wnd = nullptr;
	t_charset* charset = nullptr;

	t_screen();
	~t_screen();

	void update();
	void toggle_fullscreen();
	void draw_image(t_image* img, int x, int y);
	void putch(t_index ch, int x, int y, const t_color& fore_color);
	void putch(t_index ch, int x, int y, const t_color& fore_color, const t_color& back_color);
	void print(const t_string& str, int x, int y, const t_color& fore_color);
	void print(const t_string& str, int x, int y, const t_color& fore_color, const t_color& back_color);

private:
	void putch(t_index ch, int x, int y, const t_color& fore_color, const t_color& back_color, bool hide_back_color);
};
