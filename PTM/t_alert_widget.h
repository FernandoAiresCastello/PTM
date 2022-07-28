#pragma once
#include "common.h"

struct t_globals;
struct t_panel;

struct t_alert_widget {
	t_alert_widget(t_globals* g, string title, string text, int fgc, int bgc);
	~t_alert_widget();
	void show();
private:
	TBufferedWindow* wnd;
	TTileBuffer* buf;
	t_panel* pnl;
	string text;
};
