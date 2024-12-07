#include "t_board.h"

t_board::t_board()
{
}

t_board::~t_board()
{
	for (int layer = 0; layer < layers; layer++) {
		for (int i = 0; i < size; i++) {
			tiles[layer].clear();
		}
	}

	this->cols = 0;
	this->rows = 0;
	this->size = 0;
}

void t_board::init(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
	this->size = cols * rows;

	for (int layer = 0; layer < layers; layer++) {
		for (int i = 0; i < size; i++) {
			tiles[layer].emplace_back();
		}
	}
}

void t_board::set_tile(int layer, int x, int y, const t_tile& tile)
{
	tiles[layer][y * cols + x] = tile;
}

t_tile& t_board::get_tile(int layer, int x, int y)
{
	return tiles[layer][y * cols + x];
}

void t_board::clear()
{
	for (int layer = 0; layer < layers; layer++) {
		for (int i = 0; i < size; i++) {
			tiles[layer][i].set_empty();
		}
	}
}
