#pragma once
#include "../Common/common.h"
#include "../PTM/ptm_tile_system.h"
#include "../PTM/ptm_color_palette.h"

class ptm_system
{
public:
	ptm_system();
	~ptm_system();

	void run();

private:
	t_tileset saved_tileset;
	t_palette saved_palette;
	t_tilebuf saved_default_tilebuf;

	void init_window();
	void halt();
	void set_pal(int index, rgb color);
	void set_tilebuf_bgc(string id, int pal_index);
};
