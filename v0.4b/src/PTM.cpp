#include "PTM.h"
#include "t_tests.h"
#include "t_window.h"
#include "t_keyboard.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_tilebuffer.h"
#include "t_screen.h"
#include "t_util.h"
#include "t_main_editor.h"

t_window wnd;
t_keyboard kb;
t_charset chr;
t_palette pal;
t_screen scr;
t_main_editor main_editor;

int wnd_size = 3;

void PTM::run()
{
	if (running)
		return;

	running = true;

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

	main_editor.init(this, &scr, &kb);
}

void PTM::run_main()
{
	main_editor.print_welcome();

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
		else if (!kb.alt()) {
			kb.key = key;
			main_editor.on_keydown();
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
