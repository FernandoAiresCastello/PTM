#pragma once
#include "t_pointers.h"
#include "t_window.h"
#include "t_index.h"
#include "t_cursor.h"
#include "t_pos.h"
#include "t_list.h"
#include "t_sprite.h"

class t_charset;
class t_palette;
class t_tilebuffer;

class t_screen
{
public:
	t_screen();
	~t_screen() = default;

	void set_window(t_window* wnd);
	void set_charset(t_charset* chr);
	void set_palette(t_palette* pal);
	void draw();
	void color(t_index fgc);
	void color(t_index fgc, t_index bgc);
	void color(t_index fgc, t_index bgc, t_index bdrc);
	void locate(int x, int y);
	int last_row() const;
	int last_col() const;
	void set_tile(const t_tile& tile, int x, int y);
	void set_tile_overlay(const t_tile& tile, int x, int y);
	void set_blank_tile(int x, int y, bool monochrome);
	void print(const t_tile& tile);
	void print(const char& ch);
	void print(const t_string& str);
	void println(const t_string& str);
	void scroll_up();
	t_sptr<t_sprite> create_sprite(const t_tile& tile, const t_pos& pos);

private:
	t_window* wnd = nullptr;
	t_charset* chr = nullptr;
	t_palette* pal = nullptr;
	t_uptr<t_tilebuffer> buf_bdr;
	t_uptr<t_tilebuffer> buf;
	t_index fore_color = 15;
	t_index back_color = 1;
	t_index border_color = 10;
	t_cursor csr;
	t_pos pos = t_pos(2, 1);
	t_list<t_sptr<t_sprite>> sprites;

	void draw_sprites();
	void update_monochrome_tiles();
	void update_monochrome_tile(t_tile& tile) const;
};
