#include "t_screen.h"
#include "t_main_window.h"
#include "t_image.h"
#include "t_charset.h"

t_screen::t_screen()
{
}

t_screen::~t_screen()
{
}

void t_screen::init(t_main_window* wnd, t_charset* charset)
{
	this->wnd = wnd;
	this->charset = charset;
}

void t_screen::update()
{
	wnd->update();
}

void t_screen::clear()
{
	wnd->clear(back_color.to_rgb());
}

void t_screen::set_backcolor(const t_color& color)
{
	back_color = color;
}

const t_color& t_screen::get_backcolor() const
{
	return back_color;
}

void t_screen::toggle_fullscreen()
{
	wnd->toggle_fullscreen();
}

void t_screen::draw_image(t_image* img, int x, int y)
{
	const int px = x;
	for (int iy = 0; iy < img->get_height(); iy++) {
		for (int ix = 0; ix < img->get_width(); ix++) {
			const t_color& color = img->get_pixel(ix, iy);
			if (!img->is_transparent() || img->get_transparency_key() != color)
				wnd->set_pixel(x, y, color.to_rgb());
			
			x++;
		}
		y++;
		x = px;
	}
}

void t_screen::putch(t_index ch, int x, int y, const t_color& fore_color)
{
	putch(ch, x, y, fore_color, 0, true);
}

void t_screen::putch(t_index ch, int x, int y, const t_color& fore_color, const t_color& back_color)
{
	putch(ch, x, y, fore_color, back_color, false);
}

void t_screen::print(const t_string& str, int x, int y, const t_color& fore_color)
{
	for (auto& ch : str.s_str())
		putch(ch, x++, y, fore_color);
}

void t_screen::print(const t_string& str, int x, int y, const t_color& fore_color, const t_color& back_color)
{
	for (auto& ch : str.s_str())
		putch(ch, x++, y, fore_color, back_color);
}

void t_screen::putch(t_index ch, int x, int y, const t_color& fore_color, const t_color& back_color, bool hide_back_color)
{
	const t_binary& bits = charset->get(ch);

	x *= t_charset::char_w;
	y *= t_charset::char_h;

	const int px = x;
	for (auto& bit : bits.s_str()) {
		if (hide_back_color) {
			if (bit == '1')
				wnd->set_pixel(x, y, fore_color.to_rgb());
		}
		else {
			wnd->set_pixel(x, y, (bit == '1' ? fore_color : back_color).to_rgb());
		}
		x++;
		if (x >= px + t_charset::char_w) {
			x = px;
			y++;
		}
	}
}
