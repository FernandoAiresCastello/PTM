#pragma once
#include "t_pointers.h"
#include "t_window.h"
#include "t_index.h"
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
	void on_every_machine_cycle();
	void draw();
	void clear();
	void color(t_index fgc, t_index bgc, t_index bdrc);
	void color_fg(t_index fg);
	void color_bg(t_index bg);
	void color_bdr(t_index bdr);
	void locate(int x, int y);
	void move_cursor_dist(int dx, int dy);
	void move_cursor_wrap_x(int dx);
	int rows() const;
	int cols() const;
	int last_row() const;
	int last_col() const;
	int csrx() const;
	int csry() const;
	int eol() const;
	t_pos csr_pos() const;
	void show_cursor(bool visible);
	void set_tile(const t_tile& tile, int x, int y);
	void set_tile_at_csr(const t_tile& tile);
	void set_tile_overlay(const t_tile& tile, int x, int y);
	void set_blank_tile(int x, int y, t_tileflags flags = t_tileflags());
	void print(const t_tile& tile);
	void print(t_index ch);
	void print(const t_string& str);
	void println(const t_string& str);
	void print_lines(const t_list<t_string>& lines);
	void newline();
	void scroll_up();
	t_sptr<t_sprite> add_free_sprite(const t_tile& tile, const t_pos& pos);
	t_sptr<t_sprite> add_tiled_sprite(const t_tile& tile, const t_pos& pos);
	void remove_sprite(t_sptr<t_sprite> sprite);
	t_tile& get_tile(const t_pos& pos);
	t_tile& get_tile_at_csr();
	void set_csr_char_ix(t_index ch);
	t_string get_current_logical_line();
	t_index get_fg_color() const;
	t_index get_bg_color() const;
	t_index get_bdr_color() const;

private:
	t_window* wnd = nullptr;
	t_charset* chr = nullptr;
	t_palette* pal = nullptr;
	t_uptr<t_tilebuffer> buf_bdr;
	t_uptr<t_tilebuffer> buf;
	t_index fore_color = 15;
	t_index back_color = 1;
	t_index border_color = 10;
	t_pos pos = t_pos(2, 1);
	t_list<t_sptr<t_sprite>> sprites;
	t_sptr<t_sprite> csr;

	void init_cursor();
	void draw_sprites();
	void update_monochrome_tiles();
	void update_monochrome_tile(t_tile& tile) const;
	t_sptr<t_sprite> add_sprite(const t_tile& tile, const t_pos& pos, bool grid);
	void fix_cursor_pos();
	void update_cursor();
};
