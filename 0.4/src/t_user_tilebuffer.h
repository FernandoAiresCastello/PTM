#pragma once
#include "t_list.h"
#include "t_tile.h"

class t_user_tilebuffer
{
public:
	t_user_tilebuffer();

	void init(int cols, int rows);
	void set(const t_tile& tile, int x, int y);
	void set_blank(int x, int y);
	void rect_fill(const t_tile& tile, int x1, int y1, int x2, int y2);
	t_tile& get_ref(int x, int y);
	t_tile get_copy(int x, int y);
	void clear();
	void fill(const t_tile& tile);
	t_list<t_tile>& get_tiles();
	int width() const;
	int height() const;

private:
	int cols = 0;
	int rows = 0;
	int length = 0;
	t_list<t_tile> tiles;
};
