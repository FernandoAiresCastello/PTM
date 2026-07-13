#pragma once

struct t_pos
{
	int x = 0;
	int y = 0;

	t_pos();
	t_pos(int x, int y, bool grid = false);
	t_pos(const t_pos& other);
	
	t_pos& operator=(const t_pos& other);

	bool at(int x, int y) const;
	void set(int x, int y);
	void move(int dx, int dy);
};
