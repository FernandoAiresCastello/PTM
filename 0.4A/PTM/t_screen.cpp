#include "t_screen.h"
#include "t_main_window.h"
#include "t_image.h"

t_screen::t_screen()
{
}

t_screen::~t_screen()
{
}

void t_screen::update()
{
	wnd->update();
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
