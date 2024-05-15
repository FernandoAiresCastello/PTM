#include "t_ptm.h"
#include "t_window.h"
#include "t_keyboard.h"

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
	wnd.draw_test_frame_tiles();
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
