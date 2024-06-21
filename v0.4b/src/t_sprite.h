#pragma once
#include "t_tile.h"
#include "t_pos.h"

class t_sprite
{
public:
	t_sprite(bool grid);
	t_sprite(const t_tile& tile, const t_pos& pos, bool grid);

	t_tile& get_tile();
	const t_pos& get_pos() const;
	int get_x() const;
	int get_y() const;
	bool align_to_grid() const;

private:
	t_tile tile;
	t_pos pos;
	bool grid = false;
};
