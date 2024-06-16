#include "t_screen.h"
#include "t_tilebuffer.h"

#define border_tile		t_tile(0, border_color, border_color)

t_screen::t_screen()
{
	buf = std::make_unique<t_tilebuffer>(t_window::cols - 4, t_window::rows - 2);
	buf_bdr = std::make_unique<t_tilebuffer>();

	for (int y = 0; y < buf->rows; y++) {
		for (int x = 0; x < buf->cols; x++) {
			buf->get_ref(x, y).flags.monochrome = true;
		}
	}

	buf_bdr->fill(border_tile);

	update_monochrome_tiles();
}

void t_screen::set_window(t_window* wnd)
{
	this->wnd = wnd;
}

void t_screen::set_charset(t_charset* chr)
{
	this->chr = chr;
}

void t_screen::set_palette(t_palette* pal)
{
	this->pal = pal;
}

void t_screen::draw()
{
	buf_bdr->draw(wnd, chr, pal);
	buf->draw(wnd, chr, pal, 2, 1);
}

void t_screen::color(t_index fgc)
{
	fore_color = fgc;

	update_monochrome_tiles();
}

void t_screen::color(t_index fgc, t_index bgc)
{
	fore_color = fgc;
	back_color = bgc;

	update_monochrome_tiles();
}

void t_screen::color(t_index fgc, t_index bgc, t_index bdrc)
{
	fore_color = fgc;
	back_color = bgc;
	border_color = bdrc;

	buf_bdr->fill(border_tile);
	update_monochrome_tiles();
}

void t_screen::put(const t_tile& tile, int x, int y)
{
	buf->set(tile, x, y);
}

void t_screen::print(const t_string& str, int x, int y)
{
	buf->set_text(str, x, y, fore_color, back_color);
}

void t_screen::update_monochrome_tiles()
{
	for (int y = 0; y < buf->rows; y++) {
		for (int x = 0; x < buf->cols; x++) {
			auto& tile = buf->get_ref(x, y);
			if (tile.flags.monochrome) {
				for (auto& ch : tile.get_all_chars()) {
					ch.fgc = fore_color;
					ch.bgc = back_color;
				}
			}
		}
	}
}
