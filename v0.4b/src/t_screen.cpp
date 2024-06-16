#include "t_screen.h"
#include "t_tilebuffer.h"

t_screen::t_screen()
{
	buf = new t_tilebuffer(t_window::cols - 4, t_window::rows - 2);
	buf_bdr = new t_tilebuffer();

	for (int y = 0; y < t_window::rows; y++) {
		for (int x = 0; x < t_window::cols; x++) {
			buf->get_ref(x, y).flags.monochrome = true;
		}
	}

	update_monochrome_tiles();
}

t_screen::~t_screen()
{
	delete buf;
	buf = nullptr;
	delete buf_bdr;
	buf_bdr = nullptr;
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

	update_monochrome_tiles();
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
