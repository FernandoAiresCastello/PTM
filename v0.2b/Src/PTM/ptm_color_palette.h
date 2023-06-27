#pragma once
#include "../Common/common.h"

struct t_palette {
	vector<rgb> colors;
	t_palette();
	void reset();
	void add_blank(int count = 1);
	void add(rgb color);
	void set(int index, rgb color);
	rgb& get(int index);
	int get_r(int index);
	int get_g(int index);
	int get_b(int index);
	void set_r(int index, int value);
	void set_g(int index, int value);
	void set_b(int index, int value);
};

extern t_palette palette;

int ptm_rgb_extract_r(rgb color);
int ptm_rgb_extract_g(rgb color);
int ptm_rgb_extract_b(rgb color);
void ptm_save_palette(string file);
void ptm_load_palette(string file);
