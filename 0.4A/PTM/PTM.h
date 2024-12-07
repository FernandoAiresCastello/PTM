#pragma once
#include "global.h"
#include "t_main_window.h"
#include "t_screen.h"

class PTM
{
public:
	PTM();
	~PTM();

	int run();

private:
	t_main_window wnd;
	t_screen scr;
};

static PTM ptm;
