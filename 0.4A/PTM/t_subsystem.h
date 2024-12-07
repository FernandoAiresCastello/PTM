#pragma once
#include "t_keyboard.h"

class t_subsystem
{
public:
	t_subsystem();
	virtual ~t_subsystem();

	virtual void on_draw() = 0;
	virtual void on_keydown(t_keycode& key, t_keymod& mod) = 0;

	bool is_active() const;
	void activate();
	void deactivate();

private:
	bool active = false;
};
