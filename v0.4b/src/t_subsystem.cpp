#include "t_subsystem.h"

t_subsystem::t_subsystem()
{
}

t_subsystem::~t_subsystem()
{
}

void t_subsystem::draw(t_window* wnd, t_charset* chr, t_palette* pal)
{
	buf.draw(wnd, chr, pal);
}
