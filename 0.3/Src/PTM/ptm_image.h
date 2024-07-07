#pragma once
#include "../Common/common.h"

class t_image
{
public:
	t_image();
	~t_image();

	bool load(string filename);
	int get_width();
	int get_height();
	int get_size();
	rgb& get_pixel(int i);
	rgb& get_pixel(int x, int y);
	vector<rgb>& get_pixels();

private:
	int width;
	int height;
	int size;
	vector<rgb> pixels;
};
