#include "t_tilebuffer.h"

#define tile_at(x, y)	tiles[y * cols + x]

t_tilebuffer::t_tilebuffer()
{
	clear();
}

void t_tilebuffer::set(t_tile tile, int x, int y)
{
	tile_at(x, y) = tile;
}

t_tile& t_tilebuffer::get(int x, int y)
{
	return tile_at(x, y);
}

void t_tilebuffer::fill(t_tile tile)
{
	for (int i = 0; i < length; i++)
		tiles[i] = tile;
}

void t_tilebuffer::clear()
{
	for (int i = 0; i < length; i++)
		tiles[i].set_blank();
}
