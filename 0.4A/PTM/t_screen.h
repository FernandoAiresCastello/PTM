#pragma once
#include "global.h"

class t_main_window;

class t_screen
{
public:
	t_screen();
	~t_screen();

	t_main_window* wnd = nullptr;
};
