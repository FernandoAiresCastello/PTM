#pragma once
#include "common.h"
#include "t_ui_base.h"

struct t_board_editor : public t_ui_base {
	t_board_editor(t_globals* g);
private:
	void on_run_loop();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
};
