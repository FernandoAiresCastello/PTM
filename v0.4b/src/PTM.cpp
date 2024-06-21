#include "PTM.h"
#include "t_tests.h"
#include "t_window.h"
#include "t_keyboard.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_tilebuffer.h"
#include "t_screen.h"
#include "t_util.h"

t_window wnd;
t_keyboard kb;
t_charset chr;
t_palette pal;
t_screen scr;

int wnd_size = 3;

void PTM::run()
{
	init();
	run_tests();
	run_main();
}

void PTM::init()
{
	wnd.open(title, wnd_size);

	scr.set_window(&wnd);
	scr.set_charset(&chr);
	scr.set_palette(&pal);
}

void PTM::run_main()
{
	t_tile cursor_tile(127, 0, 0);
	cursor_tile.flags.monochrome = true;
	cursor_tile.flags.hide_bgc = true;

	scr.println("PTM 0.4");
	scr.println("Ok");
	scr.add_tiled_sprite(cursor_tile, 0, 2);

	scr.color(0xa8, 0xa3, 0xa2);

	while (wnd.is_open()) {
		update();
	}
}

void PTM::halt()
{
	while (wnd.is_open())
		update();
}

void PTM::pause(int frames)
{
	for (int i = 0; i < frames; i++) {
		if (!wnd.is_open())
			break;

		update();
	}
}

void PTM::update()
{
	scr.draw();
	wnd.update();

	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		wnd.close();
	}
	else if (e.type == SDL_KEYDOWN) {
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_RETURN && kb.alt()) {
			wnd.toggle_fullscreen();
		}
		else if (key == SDLK_ESCAPE) {
			wnd.close();
		}
	}
}

void PTM::run_tests()
{
	t_tests tests;
	tests.run();
}

void PTM::run_graphics_test()
{
	int i = 0;
	for (int y = 1; y < 1 + 16; y++) {
		for (int x = 1; x < 1 + 16; x++) {
			scr.set_tile(t_tile(0, i, i), x, y);
			i++;
		}
	}

	i = 0;
	for (int y = 1; y < 1 + 16; y++) {
		for (int x = 20; x < 20 + 16; x++) {
			scr.set_tile(t_tile(i, 15, 0), x, y);
			i++;
		}
	}

	halt();
}
