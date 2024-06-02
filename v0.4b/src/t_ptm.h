#pragma once
#include "t_window.h"
#include "t_string.h"
#include "t_keyboard.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_sys_main.h"
#include "t_sys_runtime.h"

class t_ptm
{
public:
	static constexpr auto 
		title = "PTM - Programmable Tile Machine";

	void run();

private:
	t_window wnd;
	t_keyboard kb;
	t_charset charset;
	t_palette palette;
	t_sys_main sys_main;
	t_sys_runtime sys_runtime;

	enum class t_mode {
		sys_main, sys_runtime
	}
	mode = t_mode::sys_main;

	void init();
	void quit();
	void main_loop();
	void process_sdl_events();
	void handle_keyboard(t_keycode key);

	void draw_test_frame_colors();
	void draw_test_frame_pixels();
	void draw_test_frame_chars(t_charset* charset);
};
