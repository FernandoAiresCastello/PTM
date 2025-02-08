#include "t_sprite.h"

t_sprite::t_sprite(bool grid) : tile(), pos(), grid(grid)
{
}

t_sprite::t_sprite(const t_tile& tile, const t_pos& pos, bool grid) : tile(tile), pos(pos), grid(grid)
{
}

void t_sprite::set_tile(const t_tile& tile)
{
	this->tile = tile;
}

t_tile& t_sprite::get_tile()
{
	return tile;
}

void t_sprite::set_visible(bool visible)
{
	tile.flags.visible = visible;
}

void t_sprite::set_grid(bool grid)
{
	this->grid = grid;
}

bool t_sprite::has_grid() const
{
	return grid;
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

void t_sprite::set_x(int x)
{
	pos.x = x;
}

void t_sprite::set_y(int y)
{
	pos.y = y;
}

void t_sprite::move_to(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void t_sprite::move_dist(int dx, int dy)
{
	pos.x += dx;
	pos.y += dy;
}

bool t_sprite::collides_with(t_sprite* other) const
{
	if (grid)
		return pos.x == other->pos.x && pos.y == other->pos.y;
	
	return pos.x + t_tile::width > other->pos.x && pos.x < other->pos.x + t_tile::width &&
		   pos.y + t_tile::height > other->pos.y && pos.y < other->pos.y + t_tile::height;
}
