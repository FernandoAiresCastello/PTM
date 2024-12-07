#pragma once
#include "t_rgb.h"

class t_color
{
public:
	t_color();
	t_color(RGB rgb);
	t_color(int r, int g, int b);
	t_color(const t_color& other);

	bool operator==(const t_color& other) const;
	t_color& operator=(const t_color& other);

	RGB to_rgb() const;
	static RGB pack_rgb(int r, int g, int b);
	static void unpack_rgb(RGB rgb, int* r, int* g, int* b);
	static t_color get_random();

	void set(RGB rgb);
	void set(int r, int g, int b);
	void set_r(int r);
	void set_g(int g);
	void set_b(int b);
	int get_r() const;
	int get_g() const;
	int get_b() const;

private:
	int r = 0;
	int g = 0;
	int b = 0;
};

