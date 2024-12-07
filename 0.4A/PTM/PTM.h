#pragma once
#include "global.h"
#include "t_main_window.h"
#include "t_screen.h"
#include "t_charset.h"

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
	t_charset charset;

	void on_keydown(SDL_Keycode& key, SDL_Keymod& mod);
};

static PTM ptm;
