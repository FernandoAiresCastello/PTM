#pragma once
#include <SDL.h>
#include "t_string.h"

namespace ptm
{
	const t_string wnd_title = "PTM - Programmable Tile Machine";
	const int wnd_size = 3;

	void run_tests();
	void run_graphics_test();
	void run_main();
	void halt();
}
