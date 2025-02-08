#pragma once
#include "t_pos.h"

class t_tilebuffer_region
{
public:
	int offset_x = 0;
	int offset_y = 0;
	int width = 0;
	int height = 0;

	t_tilebuffer_region() {}
	t_tilebuffer_region(int ox, int oy, int w, int h) :
		offset_x(ox), offset_y(oy), width(w), height(h) {}

	bool contains(const t_pos& pos) const
	{
		return
			pos.x >= offset_x && pos.y >= offset_y &&
			pos.x < offset_x + width && pos.y < offset_y + height;
	}
};
