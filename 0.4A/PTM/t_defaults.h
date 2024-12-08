#pragma once
#include "t_string.h"
#include "t_color.h"

struct t_defaults
{
	const t_string wnd_title = "PTM";

	const int wnd_buffer_w = 360;
	const int wnd_buffer_h = 200;
	const int wnd_stretch_w = 3;
	const int wnd_stretch_h = 3;

	const t_color back_color = 0x000000;
};
