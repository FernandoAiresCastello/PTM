#pragma once
#include "../PTM/ptm_tile_system.h"

class ptm_editor_immcmd
{
public:
	void init();
	void on_frame();

private:
	t_tilebuf* default_tilebuf = nullptr;
	t_tilebuf_layer* btm_layer = nullptr;
	t_tilebuf_layer* top_layer = nullptr;
};
