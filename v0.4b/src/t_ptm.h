#pragma once
#include <SDL.h>
#include "t_window.h"
#include "t_keyboard.h"

class t_ptm
{
public:
	void run();

private:
	t_window wnd;
	t_keyboard kb;
	t_charset charset;

	void init();
	void quit();
	void loop();
	void update();
	void handle_keyboard(SDL_Keycode key);

	void draw_test_frame_colors();
	void draw_test_frame_pixels();
	void draw_test_frame_chars(t_charset* charset);
};
