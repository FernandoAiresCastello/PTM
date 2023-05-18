#pragma once
#include "../Common/common.h"

struct t_palette {
	vector<rgb> colors;
	t_palette();
	void add_blank(int count = 1);
	void add(rgb color);
	void set(int index, rgb color);
	rgb& get(int index);
};

extern t_palette palette;
