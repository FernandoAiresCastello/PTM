#include "t_tilebuffer.h"
#include "t_window.h"
#include "t_charset.h"
#include "t_palette.h"

#define tile_at(x, y)			tiles[y * cols + x]
#define if_inside_bounds(x, y)	if (x >= 0 && y >= 0 && x < cols && y < rows)
#define if_out_of_bounds(x, y)	if (x < 0 || y < 0 || x >= cols || y >= rows)

t_tilebuffer::t_tilebuffer() : t_tilebuffer(t_window::cols, t_window::rows)
{
}

t_tilebuffer::t_tilebuffer(int cols, int rows) : 
	cols(cols), rows(rows), length(cols * rows)
{
	for (int i = 0; i < length; i++)
		tiles.emplace_back();

	clear();
}

int t_tilebuffer::last_row() const
{
	return rows - 1;
}

int t_tilebuffer::last_col() const
{
	return cols - 1;
}

void t_tilebuffer::draw(t_window* wnd, t_charset* chr, t_palette* pal)
{
	draw(wnd, chr, pal, 0, 0);
}

void t_tilebuffer::draw(t_window* wnd, t_charset* chr, t_palette* pal, int px, int py)
{
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			t_tile& tile = tile_at(x, y);
			draw_tile(tile, wnd, chr, pal, px + x, py + y);
		}
	}
}

void t_tilebuffer::draw_tile(t_tile& tile, t_window* wnd, t_charset* chr, t_palette* pal, int x, int y) const
{
	if (tile.flags.visible) {
		t_char& ch = tile.get_char_wraparound(wnd->get_animation_frame());
		wnd->draw_pixels(chr->get(ch.ix), x, y, pal->get(ch.fgc), pal->get(ch.bgc), true, tile.flags.hide_bgc);
	}
}

void t_tilebuffer::set(const t_tile& tile, int x, int y)
{
	if_inside_bounds(x, y)
		tile_at(x, y) = tile;
}

void t_tilebuffer::set_text(const t_string& text, int x, int y, t_index fgc, t_index bgc, t_tileflags flags)
{
	for (auto& ch : text.s_str()) {
		if_out_of_bounds(x, y)
			break;
		
		tile_at(x, y) = t_tile(ch, fgc, bgc, flags);
		tile_at(x, y).flags = flags;

		x++;
	}
}

int t_tilebuffer::set_text_wrap(const t_string& text, int* xptr, int* yptr, t_index fgc, t_index bgc, t_tileflags flags)
{
	int& x = *xptr;
	int& y = *yptr;
	int ix = 0;

	for (auto& ch : text.s_str()) {
		tile_at(x, y) = t_tile(ch, fgc, bgc, flags);
		if (x == last_col()) {
			tile_at(x, y).flags.line_wrap = true;
		}
		ix++;
		x++;
		if (x >= cols) {
			x = 0;
			y++;
			if (y >= rows) {
				break;
			}
		}
	}
	return ix;
}

void t_tilebuffer::set_blank(int x, int y)
{
	if_inside_bounds(x, y)
		tile_at(x, y).set_blank();
}

t_tile& t_tilebuffer::get_ref(int x, int y)
{
	return tile_at(x, y);
}

t_tile t_tilebuffer::get_copy(int x, int y) const
{
	return tile_at(x, y);
}

void t_tilebuffer::fill(const t_tile& tile)
{
	for (int i = 0; i < length; i++)
		tiles[i] = tile;
}

void t_tilebuffer::clear()
{
	for (int i = 0; i < length; i++)
		tiles[i].set_blank();
}
