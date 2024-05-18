#include "t_ptm.h"
#include "t_window.h"
#include "t_keyboard.h"
#include "t_util.h"

#define APP_TITLE	"PTM"

void t_ptm::run()
{
	init();
	
	while (wnd.is_open())
		loop();

	quit();
}

void t_ptm::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wnd.create(APP_TITLE);
}

void t_ptm::quit()
{
	wnd.close();
	SDL_Quit();
}

void t_ptm::loop()
{
	draw_test_frame_chars(&charset);
	wnd.draw_text(&charset, "Hello World!", 1, 1, 0xff0000, 0xffff00, true);

	update();
}

void t_ptm::update()
{
	wnd.update();

	SDL_Event e = { 0 };

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			wnd.close();
		}
		else if (e.type == SDL_KEYDOWN) {
			handle_keyboard(e.key.keysym.sym);
		}
	}
}

void t_ptm::handle_keyboard(SDL_Keycode key)
{
	if (kb.alt() && key == SDLK_RETURN) {
		wnd.toggle_fullscreen();
	}
}

void t_ptm::draw_test_frame_colors()
{
	wnd.clear(t_color::get_random());
}

void t_ptm::draw_test_frame_pixels()
{
	for (int y = 0; y < wnd.height(); y++) {
		for (int x = 0; x < wnd.width(); x++) {
			wnd.draw_pixel(x, y, t_color::get_random());
		}
	}
}

void t_ptm::draw_test_frame_chars(t_charset* charset)
{
	for (int y = 0; y < wnd.rows(); y++) {
		for (int x = 0; x < wnd.cols(); x++) {
			wnd.draw_char(charset, t_util::rnd(0, 255),
				x, y, t_color::get_random(), t_color::get_random(), true);
		}
	}
}
