#include "t_tilebuffer.h"
#include "t_window.h"
#include "t_charset.h"
#include "t_palette.h"

#define tile_at(x, y)	tiles[y * cols + x]

t_tilebuffer::t_tilebuffer(int cols, int rows) : 
	cols(cols), rows(rows), length(cols * rows)
{
	tiles = new t_tile[length];
	clear();
}

t_tilebuffer::~t_tilebuffer()
{
	delete[] tiles;
	tiles = nullptr;
}

void t_tilebuffer::set(t_tile tile, int x, int y)
{
	tile_at(x, y) = tile;
}

t_tile& t_tilebuffer::get_ref(int x, int y)
{
	return tile_at(x, y);
}

t_tile t_tilebuffer::get_copy(int x, int y) const
{
	return tile_at(x, y);
}

void t_tilebuffer::fill(t_tile tile)
{
	for (int i = 0; i < length; i++)
		tiles[i] = tile;
}

void t_tilebuffer::clear()
{
	for (int i = 0; i < length; i++)
		tiles[i].set_blank();
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
