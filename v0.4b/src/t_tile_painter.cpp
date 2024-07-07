#include "t_tile_painter.h"
#include "t_screen.h"
#include "t_list.h"

void t_tile_painter::init(t_screen* scr)
{
	this->scr = scr;
}

void t_tile_painter::paint(const t_string& cmd_line)
{
	for (const auto& ch : cmd_line.s_str()) {

	}
}
