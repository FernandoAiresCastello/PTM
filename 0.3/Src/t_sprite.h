#pragma once
#include "t_tile.h"
#include "t_pos.h"
#include "t_pointers.h"

class t_sprite
{
public:
	friend class t_screen;

	bool enabled = false;

	t_sprite(bool grid);
	t_sprite(const t_tile& tile, const t_pos& pos, bool grid, bool visible, bool transparent);
	t_sprite(const t_sprite& other);

	void set_tile(const t_tile& tile);
	t_tile& get_tile();
	void set_visible(bool visible);
	void set_grid(bool grid);
	bool has_grid() const;
	bool is_visible() const;
	bool is_transparent() const;
	const t_pos& get_pos() const;
	int get_x() const;
	int get_y() const;
	void set_x(int x);
	void set_y(int y);
	void move_to(int x, int y);
	void move_dist(int dx, int dy);
	bool collides_with(t_sprite* other) const;

private:
	t_tile tile;
	t_pos pos;
	bool grid = false;
};

using t_sprite_ptr = t_sptr<t_sprite>;
