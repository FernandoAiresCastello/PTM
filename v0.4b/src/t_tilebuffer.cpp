#include "t_tilebuffer.h"
#include "t_window.h"
#include "t_charset.h"
#include "t_palette.h"

#define tile_at(x, y)	tiles[y * cols + x]

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

void t_tilebuffer::draw(t_window* wnd, t_charset* chr, t_palette* pal)
{
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			t_char& ch = tile_at(x, y).get_char_wraparound(wnd->get_animation_frame());
			wnd->draw_pixels(chr->get(ch.ix), x, y, pal->get(ch.fgc), pal->get(ch.bgc), true);
		}
	}
}

void t_tilebuffer::draw(t_window* wnd, t_charset* chr, t_palette* pal, int px, int py)
{
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			t_char& ch = tile_at(x, y).get_char_wraparound(wnd->get_animation_frame());
			wnd->draw_pixels(chr->get(ch.ix), px + x, py + y, pal->get(ch.fgc), pal->get(ch.bgc), true);
		}
	}
}

void t_tilebuffer::set(const t_tile& tile, int x, int y)
{
	tile_at(x, y) = tile;
}

void t_tilebuffer::set_text(const t_string& text, int x, int y, t_index fgc, t_index bgc)
{
	for (auto& ch : text.s_str()) {
		tile_at(x++, y) = t_tile(ch, fgc, bgc);
	}
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
