#include "t_pos.h"
#include "t_tile.h"

t_pos::t_pos() : x(0), y(0)
{
}

t_pos::t_pos(int x, int y, bool grid) : x(x), y(y)
{
	if (grid) {
		this->x *= t_tile::width;
		this->y *= t_tile::height;
	}
}

t_pos::t_pos(const t_pos& other) : x(other.x), y(other.y)
{
}

t_pos& t_pos::operator=(const t_pos& other)
{
	if (this == &other)
		return *this;

	x = other.x;
	y = other.y;

	return *this;
}

bool t_pos::at(int x, int y) const
{
	return this->x == x && this->y == y;
}

void t_pos::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

void t_pos::move(int dx, int dy)
{
	x += dx;
	y += dy;
}
