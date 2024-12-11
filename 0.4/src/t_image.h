#pragma once
#include "t_color.h"
#include "t_string.h"
#include "t_list.h"

class t_image
{
public:
	t_image(int width, int height, t_rgb color);
	t_image(const t_string& file_path);
	~t_image();

	void load(const t_string& file_path);
	void set_pixel(int x, int y, t_rgb color);
	t_rgb get_pixel(int x, int y);
	void set_transparent(t_rgb color);
	void set_opaque();
	bool is_transparent() const;
	t_rgb get_transparency_key() const;
	t_list<t_rgb>& get_pixels();
	
private:
	friend class t_window;

	t_list<t_rgb> pixels;
	int width = 0;
	int height = 0;
	bool transparent = false;
	t_rgb transparency_key = 0x000000;
};
