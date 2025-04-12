#pragma once
#include "PTMLIB_Global.h"

namespace PTMLIB
{
	using t_rgb = int;

	void PTMAPI ptm_init(int size);
	void PTMAPI ptm_destroy();
	void PTMAPI ptm_clear_window(t_rgb color);
	void PTMAPI ptm_update_window();
}
