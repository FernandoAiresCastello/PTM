#pragma once
#include "t_subsystem.h"

class t_sys_runtime : public t_subsystem
{
public:
	virtual void on_init() override;
	virtual void on_loop() override;
	virtual void on_keypress(t_keyboard* kb) override;
};
