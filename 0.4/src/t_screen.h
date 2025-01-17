#pragma once
#include "t_pointers.h"
#include "t_window.h"
#include "t_index.h"
#include "t_pos.h"
#include "t_list.h"
#include "t_sprite.h"
#include "t_tilebuffer_region.h"

class PTM;
class t_charset;
class t_palette;
class t_tilebuffer;
class t_keyboard;

enum class t_color_mode
{
	mode0_monochrome, mode1_multicolor
};

class t_screen
{
public:
	const int cols;
	const int rows;
	const int last_col;
	const int last_row;
	const int default_fg = 0x0d;
	const int default_bg = 0xcf;
	const int default_bdr = 0xce;

	t_screen(int cols, int rows);
	~t_screen() = default;

	void reset();
	void set_window(t_window* wnd);
	void set_charset(t_charset* chr);
	void set_palette(t_palette* pal);
	void refresh();
	void draw();
	void clear();
	void set_color_mode(t_color_mode color_mode);
	void color(t_index fgc, t_index bgc, t_index bdrc);
	void color_fg(t_index fg);
	void color_bg(t_index bg);
	void color_bdr(t_index bdr);
	void locate(int x, int y);
	void move_cursor_dist(int dx, int dy);
	void move_cursor_top_left();
	void move_cursor_line_start();
	void move_cursor_eol();
	void move_cursor_next_logical_x(int dist);
	int csrx() const;
	int csry() const;
	int eol() const;
	t_pos csr_pos() const;
	void show_cursor(bool visible);
	void set_tile(const t_tile& tile, int x, int y);
	void set_tile_at_csr(const t_tile& tile);
	void set_blank_tile(int x, int y, t_tileflags flags = t_tileflags());
	void set_blank_tile_at_csr(t_tileflags flags = t_tileflags());
	t_tile create_blank_tile(t_tileflags flags = t_tileflags());
	void on_character_key_pressed(t_index ch);
	void on_backspace_pressed();
	void on_delete_pressed();
	void print_char(t_index ch);
	void print_tile(const t_tile& tile);
	void print_string(const t_string& str);
	void print_string_crlf(const t_string& str, bool allow_scroll = true);
	void print_string_at(const t_string& str, int x, int y);
	bool print_lines(const t_list<t_string>& lines, PTM* ptm);
	bool print_lines_with_icon(const t_list<t_tile>& icons, const t_list<t_string>& lines, PTM* ptm);
	void print_debug(const t_string& str);
	void newline(bool allow_scroll = true);
	void scroll_up_for_text_editor();
	void scroll_vertical(int dist);
	void scroll_horizontal(int dist);
	void scroll_to(int x, int y);
	t_tile& get_tile(const t_pos& pos);
	t_tile& get_tile_at_csr();
	void set_csr_char_ix(t_index ch);
	bool is_cursor_on_logical_line();
	t_string get_current_logical_line();
	void reset_horizontal_scroll();
	void reset_vertical_scroll();
	void sync_horizontal_scroll();
	void sync_vertical_scroll();
	t_index get_fg_color() const;
	t_index get_bg_color() const;
	t_index get_bdr_color() const;
	void fill(const t_tile& tile);
	void rect_fill(const t_tile& tile, int x1, int y1, int x2, int y2);
	void rect_border(const t_tile& tile, int x1, int y1, int x2, int y2);
	void rect_clear(int x1, int y1, int x2, int y2);
	void toggle_insert_mode();
	void set_insert_mode(bool state);
	bool displace_tiles_right();
	bool displace_tiles_left();
	const t_tilebuffer_region& get_viewport();
	void delete_all_sprites();

private:
	t_window* wnd = nullptr;
	t_charset* chr = nullptr;
	t_palette* pal = nullptr;
	t_uptr<t_tilebuffer> buf;
	t_index fore_color = 15;
	t_index back_color = 1;
	t_index border_color = 10;
	t_pos buf_pos = t_pos(2, 1);
	t_tilebuffer_region viewport;
	t_sprite_ptr csr;
	t_color_mode color_mode = t_color_mode::mode0_monochrome;
	t_string logical_line;
	bool insert_mode = false;
	bool printing_lines = false;

	void update_monochrome_tiles();
	void update_monochrome_tile(t_tile& tile) const;
	void fix_cursor_pos();
	void update_cursor();
	void clear_background();
	void fix_horizontal_scroll();
	void fix_vertical_scroll();
};
