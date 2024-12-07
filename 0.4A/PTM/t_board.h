#pragma once
#include "t_tile.h"
#include "t_list.h"

class t_board
{
public:
	t_board();
	~t_board();

	void init(int cols, int rows);
	void set_tile(int layer, int x, int y, const t_tile& tile);
	t_tile& get_tile(int layer, int x, int y);
	void clear();

private:
	static const int layers = 3;

	int cols = 0;
	int rows = 0;
	int size = 0;

	t_list<t_tile> tiles[layers];
};
