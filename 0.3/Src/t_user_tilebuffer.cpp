#include "t_user_tilebuffer.h"

t_user_tilebuffer::t_user_tilebuffer()
{
}

void t_user_tilebuffer::init(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
	this->length = cols * rows;

	tiles.clear();
	for (int i = 0; i < length; i++)
		tiles.emplace_back(t_tile::create_blank());
}

void t_user_tilebuffer::set(const t_tile& tile, int x, int y)
{
	if (x >= 0 && y >= 0 && x < cols && y < rows)
		tiles[y * cols + x] = tile;
}

void t_user_tilebuffer::set_blank(int x, int y)
{
	if (x >= 0 && y >= 0 && x < cols && y < rows)
		tiles[y * cols + x].set_blank();
}

void t_user_tilebuffer::rect_fill(const t_tile& tile, int x1, int y1, int x2, int y2)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++)
			set(tile, x, y);
}

t_tile& t_user_tilebuffer::get_ref(int x, int y)
{
	return tiles[y * cols + x];
}

t_tile t_user_tilebuffer::get_copy(int x, int y)
{
	if (x >= 0 && y >= 0 && x < cols && y < rows)
		return tiles[y * cols + x];

	return t_tile::create_blank();
}

void t_user_tilebuffer::clear()
{
	for (int i = 0; i < length; i++)
		tiles[i].set_blank();
}

void t_user_tilebuffer::fill(const t_tile& tile)
{
	for (int i = 0; i < length; i++)
		tiles[i] = tile;
}

t_list<t_tile>& t_user_tilebuffer::get_tiles()
{
	return tiles;
}

int t_user_tilebuffer::width() const
{
	return cols;
}

int t_user_tilebuffer::height() const
{
	return rows;
}
