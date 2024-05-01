#include "t_ptm.h"
#include "t_window.h"
#include "t_keyboard.h"

void t_ptm::run()
{
	init();
	while (wnd.is_open()) loop();
	quit();
}

void t_ptm::init()
{
	srand((unsigned int)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	wnd.create("PTM");
}

void t_ptm::quit()
{
	wnd.close();
	SDL_Quit();
}

void t_ptm::loop()
{
	wnd.draw_test_frame_tiles();
	wnd.draw_text("Hello World!", 1, 1, 0x000000, 0xffffff, true);
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
			if (e.key.keysym.sym == SDLK_RETURN && kb.alt()) {
				wnd.toggle_fullscreen();
			}
		}
	}
}
