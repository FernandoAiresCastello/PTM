#pragma once
#include "t_pointers.h"
#include "t_sprite.h"
#include "t_tile.h"
#include "t_pos.h"
#include "t_tilebuffer_region.h"
#include "t_spritelist.h"

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

	t_spritelist sprites;
	bool sprites_enabled = true;

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
	t_list<t_tile>& get_tiles();
	t_sprite_ptr get_cursor();
	int get_loaded_back_color() const;
	void save(const t_string& filename, int back_color);
	bool load(const t_string& filename);

private:
	const int length;

	t_list<t_tile> tiles;
	t_sprite_ptr cursor_sprite;
	int loaded_back_color = -1;

	void draw_tile_absolute_pos(t_tile& tile, t_window* wnd, t_charset* chr, t_palette* pal, int x, int y, bool grid) const;
};
