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
	api.init_window();
	show_intro();

	api.halt();
}
void ptm_system::show_intro()
{
	api.default_buf();
	api.layer(0);
	api.cls();
	api.color(1, 0);
	api.print(1, 1, "PTM 0.3b");
	api.beep();
	api.pause(2000);
	api.cls();
}
