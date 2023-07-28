#include "ptm_editor_immcmd.h"
#include "../PTM/ptm_core.h"
#include "../PTM/ptm_graphics_base.h"

void ptm_editor_immcmd::init()
{
	default_tilebuf = ptm_get_default_tilebuffer();
	btm_layer = &default_tilebuf->layer(0);
	top_layer = &default_tilebuf->layer(1);
}
void ptm_editor_immcmd::on_frame()
{
	
}
