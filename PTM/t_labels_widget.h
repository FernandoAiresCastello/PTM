#pragma once
#include "common.h"

struct t_globals;
struct t_program;
struct t_list_widget;

struct t_labels_widget {
	t_labels_widget(t_globals* g, string title, int x, int y, int w, int h,
		int fgc, int bgc, int sel_fgc, int sel_bgc);
	~t_labels_widget();
	string select_label(t_program* prg);
private:
	TBufferedWindow* wnd;
	t_list_widget* list;
	void populate_list(t_program* prg);
};
