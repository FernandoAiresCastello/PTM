#include "t_screen.h"
#include "t_window.h"
#include "t_charset.h"
#include "t_palette.h"

t_screen::t_screen()
{
}

void t_screen::draw(t_window* wnd, t_charset* chr, t_palette* pal)
{
	buf.draw(wnd, chr, pal);
}
