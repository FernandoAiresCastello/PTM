#pragma once
#include "t_system.h"
#include "t_keyboard.h"
#include "t_main_window.h"
#include "t_screen.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_image_pool.h"

struct t_ptm {
	const t_index invalid_index = -1;

	t_system sys;
	t_keyboard kb;
	t_main_window wnd;
	t_screen scr;
	t_charset font;
	t_palette palette;
	t_image_pool images;
};

extern t_ptm ptm;
