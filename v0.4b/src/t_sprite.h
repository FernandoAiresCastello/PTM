#pragma once
#include "t_tile.h"
#include "t_pos.h"

class t_sprite
{
public:
	t_tile tile;
	t_pos pos;

	t_sprite();
	t_sprite(const t_tile& tile, const t_pos& pos);
};
