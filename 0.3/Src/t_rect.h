#pragma once

struct t_rect {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	t_rect() : x(0), y(0), w(0), h(0) {}
	t_rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
};
