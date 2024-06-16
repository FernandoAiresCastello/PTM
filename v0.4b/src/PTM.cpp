#include "PTM.h"
#include "t_tests.h"
#include "t_window.h"
#include "t_keyboard.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_tilebuffer.h"
#include "t_screen.h"

namespace ptm
{
	t_window wnd;
	t_keyboard kb;
	t_charset chr;
	t_palette pal;
	t_screen scr;
}

void ptm::init()
{
	wnd.open(wnd_title, wnd_size);

	scr.set_window(&wnd);
	scr.set_charset(&chr);
	scr.set_palette(&pal);
}

void ptm::run_tests()
{
	t_tests tests;
	tests.run();
}

void ptm::run_graphics_test()
{
	int i = 0;
	for (int y = 1; y < 1 + 16; y++) {
		for (int x = 1; x < 1 + 16; x++) {
			scr.put(t_tile(0, i, i), x, y);
			i++;
		}
	}

	i = 0;
	for (int y = 1; y < 1 + 16; y++) {
		for (int x = 20; x < 20 + 16; x++) {
			scr.put(t_tile(i, 15, 0), x, y);
			i++;
		}
	}

	halt();
}

void ptm::run_main()
{
	scr.color(0x3a, 0x38, 0x31);
	scr.print("Hello World!", 0, 0);

	halt();
}

void ptm::halt()
{
	while (wnd.is_open()) {
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
}
