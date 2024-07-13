#pragma once

struct t_tilebuffer_region
{
	int offset_x = 0;
	int offset_y = 0;
	int width = 0;
	int height = 0;

	t_tilebuffer_region() {}
	t_tilebuffer_region(int ox, int oy, int w, int h) :
		offset_x(ox), offset_y(oy), width(w), height(h) {}
};
