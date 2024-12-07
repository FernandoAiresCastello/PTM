#pragma once
#include "t_keyboard.h"
#include "t_list.h"

class t_subsystem;

class t_system
{
public:
	t_system();
	~t_system();

	int run();
	void quit();

private:
	t_list<t_subsystem*> subsystems;

	void on_draw();
	void on_keydown(t_keycode& key, t_keymod& mod);
};
