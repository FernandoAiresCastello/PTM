#include "t_sprite.h"

t_sprite::t_sprite(bool grid) : tile(), pos(), grid(grid)
{
}

t_sprite::t_sprite(const t_tile& tile, const t_pos& pos, bool grid) : tile(tile), pos(pos), grid(grid)
{
}

t_tile& t_sprite::get_tile()
{
	return tile;
}

const t_pos& t_sprite::get_pos() const
{
	return pos;
}

int t_sprite::get_x() const
{
	return pos.x;
}

int t_sprite::get_y() const
{
	return pos.y;
}

bool t_sprite::align_to_grid() const
{
	return grid;
}
