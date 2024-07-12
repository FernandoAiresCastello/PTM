#pragma once
#include "t_tile.h"
#include "t_pos.h"

class t_sprite
{
public:
	friend class t_screen;

	t_sprite(bool grid);
	t_sprite(const t_tile& tile, const t_pos& pos, bool grid);

	void set_tile(const t_tile& tile);
	t_tile& get_tile();
	void set_visible(bool visible);
	bool align_to_grid() const;
	const t_pos& get_pos() const;
	int get_x() const;
	int get_y() const;
	void set_x(int x);
	void set_y(int y);
	void move_to(int x, int y);
	void move_dist(int dx, int dy);

private:
	t_tile tile;
	t_pos pos;
	bool grid = false;
};
