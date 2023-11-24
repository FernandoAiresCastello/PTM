#include "ptm_api.h"
#include "../PTM/ptm_core.h"
#include "../PTM/ptm_tile_system.h"
#include "../PTM/ptm_color_palette.h"

void ptm_api::init_window()
{
	ptm_init_window(360, 200, 3, 0x000000, 2);
}
void ptm_api::halt()
{
	ptm_halt();
}
