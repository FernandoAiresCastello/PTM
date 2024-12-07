#pragma once
#include "t_subsystem.h"

class t_sys_test : public t_subsystem
{
	void on_draw() override;
	void on_keydown(t_keycode& key, t_keymod& mod) override;
};
