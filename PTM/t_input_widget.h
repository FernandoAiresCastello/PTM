#pragma once
#include "common.h"

struct t_globals;
struct t_panel;

struct t_input_widget {
	t_input_widget(t_globals* g, string title, int fgc, int bgc);
	t_input_widget(t_globals* g, string title, string text, int fgc, int bgc);
	t_input_widget(t_globals* g, string title, string text, 
		int maxlen, int fgc, int bgc, int x, int y);
	~t_input_widget();
	string show();
private:
	TBufferedWindow* wnd;
	TTileBuffer* buf;
	t_panel* pnl;
	string initial_str;
	int maxlen;
};
