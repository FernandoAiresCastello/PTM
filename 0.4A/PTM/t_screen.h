#pragma once
#include "global.h"

class t_main_window;
class t_image;

class t_screen
{
public:
	t_main_window* wnd = nullptr;

	t_screen();
	~t_screen();

	void update();
	void draw_image(t_image* img, int x, int y);
};
