#pragma once
#include <SDL.h>
#include "t_window.h"
#include "t_string.h"
#include "t_keyboard.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_screen.h"

class t_ptm
{
public:
	static constexpr auto title = "PTM - Programmable Tile Machine";

	void run();

private:
	t_window wnd;
	t_keyboard kb;
	t_charset charset;
	t_palette palette;
	t_screen screen;

	void init();
	void quit();
	void loop();
	void update();
	void handle_keyboard(SDL_Keycode key);

	void draw_test_frame_colors();
	void draw_test_frame_pixels();
	void draw_test_frame_chars(t_charset* charset);
};
