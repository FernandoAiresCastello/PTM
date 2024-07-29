#pragma once
#include "t_pointers.h"
#include "t_sprite.h"
#include "t_tile.h"
#include "t_pos.h"
#include "t_tilebuffer_region.h"

class t_window;
class t_charset;
class t_palette;

class t_tilebuffer
{
public:
	const int cols;
	const int rows;
	const int last_row;
	const int last_col;

	t_tilebuffer();
	t_tilebuffer(int cols, int rows);
	~t_tilebuffer() = default;

	void draw(t_window* wnd, t_charset* chr, t_palette* pal, const t_pos& scr_pos, const t_tilebuffer_region& region);
	void set(const t_tile& tile, int x, int y);
	void set_text(const t_string& text, int x, int y, t_index fgc, t_index bgc, t_tileflags flags = t_tileflags());
	void set_blank(int x, int y);
	t_tile& get_ref(int x, int y);
	t_tile get_copy(int x, int y) const;
	void fill(const t_tile& tile);
	void clear();
	t_sptr<t_sprite> add_sprite(const t_tile& tile, const t_pos& pos, bool grid);
	t_list<t_sptr<t_sprite>>& get_sprites();
	void delete_sprite(t_sptr<t_sprite> sprite);
	void delete_all_sprites();
	t_sptr<t_sprite> get_cursor();

private:
	const int length;

	t_list<t_tile> tiles;
	t_list<t_sptr<t_sprite>> sprites;
	t_sptr<t_sprite> cursor_sprite;

	void draw_sprites(t_window* wnd, t_charset* chr, t_palette* pal);
	void draw_tile_absolute_pos(t_tile& tile, t_window* wnd, t_charset* chr, t_palette* pal, int x, int y, bool grid) const;
};
