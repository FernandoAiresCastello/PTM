#include "ptm_system.h"
#include "../PTM/ptm_core.h"
#include "../PTM/ptm_graphics_base.h"

ptm_system::ptm_system()
{
}
ptm_system::~ptm_system()
{
}
void ptm_system::run()
{
	init_window();
	halt();
}
void ptm_system::init_window()
{
	ptm_init_window(360, 200, 3, 0x000000, 1);
}
void ptm_system::halt()
{
	ptm_halt();
}
void ptm_system::set_pal(int index, rgb color)
{
	palette.set(index, color);
}
void ptm_system::set_tilebuf_bgc(string id, int pal_index)
{
	tilebufs.get(id)->set_bgcol(pal_index);
}
