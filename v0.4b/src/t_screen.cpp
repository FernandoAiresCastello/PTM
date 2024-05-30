#include "t_screen.h"
#include "t_tilebuffer.h"

t_screen::t_screen()
{
}

void t_screen::set_tilebuf(t_tilebuffer* buf)
{
	this->buf = buf;
}
