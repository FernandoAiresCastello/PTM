#pragma once
#include "common.h"
#include "t_window.h"
#include "t_keyboard.h"

class t_ptm
{
public:
	void run();

private:
	t_window wnd;
	t_keyboard kb;

	void init();
	void quit();
	void loop();
	void update();
};
