#pragma once
#include "t_color.h"
#include "t_list.h"
#include "t_string.h"

class t_image
{
public:
	t_image();
	t_image(int w, int h, const t_color& back_color = 0xffffff);
	~t_image();

	void set_pixel(int x, int y, const t_color& color);
	const t_color& get_pixel(int x, int y) const;
	void set_transparency_key(const t_color& color);
	const t_color& get_transparency_key() const;
	void set_transparent(bool transp);
	bool is_transparent() const;
	int get_width() const;
	int get_height() const;
	bool load(const t_string& filename);

private:
	int width = 0;
	int height = 0;
	t_list<t_color> pixels;
	bool transparent = false;
	t_color transparency_key;
};
