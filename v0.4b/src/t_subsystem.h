#pragma once
#include "t_tilebuffer.h"

class t_window;
class t_charset;
class t_palette;
class t_keyboard;

class t_subsystem
{
public:
	t_subsystem();
	virtual ~t_subsystem();

	virtual void on_init() = 0;
	virtual void on_loop() = 0;
	virtual void on_keypress(t_keyboard* kb) = 0;

	void draw(t_window* wnd, t_charset* chr, t_palette* pal);

protected:
	t_tilebuffer buf;
};
