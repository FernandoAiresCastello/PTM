#pragma once
#include "t_tile.h"
#include "t_window.h"

class t_tilebuffer
{
public:
	static constexpr int cols = t_window::cols;
	static constexpr int rows = t_window::rows;

	t_tilebuffer();

	void set(t_tile tile, int x, int y);
	t_tile& get(int x, int y);
	void fill(t_tile tile);
	void clear();

private:
	static constexpr int length = rows * cols;

	t_tile tiles[length];
};
