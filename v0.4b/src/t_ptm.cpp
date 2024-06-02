#include <SDL.h>
#include "t_ptm.h"
#include "t_window.h"
#include "t_keyboard.h"
#include "t_util.h"

void t_ptm::run()
{
	init();

	while (wnd.is_open())
		main_loop();

	quit();
}

void t_ptm::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	wnd.create(title, 3);
	wnd.reset_frame_counter();

	sys_main.on_init();
	sys_runtime.on_init();
}

void t_ptm::quit()
{
	wnd.close();
	SDL_Quit();
}

void t_ptm::main_loop()
{
	if (mode == t_mode::sys_main) {
		sys_main.on_loop();
		sys_main.draw(&wnd, &charset, &palette);
	}
	else if (mode == t_mode::sys_runtime) {
		sys_runtime.on_loop();
		sys_runtime.draw(&wnd, &charset, &palette);
	}

	wnd.update();
	process_sdl_events();
}

void t_ptm::process_sdl_events()
{
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

void t_ptm::handle_keyboard(t_keycode key)
{
	kb.key = key;

	if (kb.alt() && key == SDLK_RETURN) {
		wnd.toggle_fullscreen();
	}
	else {
		if (mode == t_mode::sys_main) {
			sys_main.on_keypress(&kb);
		}
		else if (mode == t_mode::sys_runtime) {
			sys_runtime.on_keypress(&kb);
		}
	}
}

void t_ptm::draw_test_frame_colors()
{
	wnd.clear(t_color::get_random());
}

void t_ptm::draw_test_frame_pixels()
{
	for (int y = 0; y < t_window::image_h; y++) {
		for (int x = 0; x < t_window::image_w; x++) {
			wnd.draw_pixel(x, y, t_color::get_random());
		}
	}
}

void t_ptm::draw_test_frame_chars(t_charset* charset)
{
	for (int y = 0; y < t_window::rows; y++) {
		for (int x = 0; x < t_window::cols; x++) {
			wnd.draw_char(charset, t_util::rnd(0, 255),
				x, y, t_color::get_random(), t_color::get_random(), true);
		}
	}
}
