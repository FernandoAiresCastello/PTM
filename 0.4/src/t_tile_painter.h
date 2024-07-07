#pragma once
#include "t_string.h"

class t_screen;

class t_tile_painter
{
public:
	void init(t_screen* scr);
	void paint(const t_string& cmd_line);

private:
	t_screen* scr = nullptr;
};
