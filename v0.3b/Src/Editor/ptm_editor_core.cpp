#include "ptm_editor_core.h"
#include "../PTM/ptm_core.h"
#include "../PTM/ptm_graphics_base.h"

void ptm_editor_core::run()
{
	mode = ptm_editor_mode::immcmd;

	SDL_Init(SDL_INIT_EVERYTHING);
	ptm_init_window(360, 200, 3, 0x000000, 2);
	immcmd.init();
	//ptm_editor_prgedit_init();

	bool editor_running = true;
	while (editor_running) {
		if (mode == ptm_editor_mode::immcmd) {
			immcmd.on_frame();
		}
		else if (mode == ptm_editor_mode::prgedit) {
			//ptm_editor_prgedit_on_frame();
		}
		ptm_update();
	}
}
