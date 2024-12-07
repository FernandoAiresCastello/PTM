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
	void quit();

private:
	t_main_window wnd;
	t_screen scr;

	void on_keydown(SDL_Keycode& key);
};

static PTM ptm;
