#pragma once
#include "t_keyboard.h"
#include "t_list.h"
#include "t_sys_test.h"

class t_subsystem;

class t_system
{
public:
	t_sys_test sys_test;

	t_system();
	~t_system();

	int run();
	void quit();

private:
	t_list<t_subsystem*> subsystems;

	void add_subsystem(t_subsystem* sys);

	void on_draw();
	void on_keydown(t_keycode& key, t_keymod& mod);
};
