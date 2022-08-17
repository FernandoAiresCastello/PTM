#pragma once
#include "common.h"

struct t_globals;
struct t_panel;

struct t_list_widget_item {
	TTileSeq icon;
	string text;
	string data;
};
struct t_list_widget {
	t_list_widget(t_globals* g, string title, int x, int y, int w, int h, 
		int fgc, int bgc, int sel_fgc, int sel_bgc);
	~t_list_widget();
	void add_item(t_list_widget_item item);
	void add_item(string text, string data = "", TTileSeq icon = TTileSeq());
	void clear();
	void draw();
	void select(int index);
	void select_next();
	void select_prev();
	void reset_selection();
	t_list_widget_item* get_selected_item();
	int get_selected_index();
	t_panel* get_panel();
	void sort_alphabetically();
	t_list_widget_item* run_default_selection_loop(SDL_Keycode alt_confirm_key = SDLK_RETURN);
	void auto_resize();
	void stretch(int dx, int dy);
private:
	TBufferedWindow* wnd;
	TTileBuffer* buf;
	t_panel* pnl;
	std::vector<t_list_widget_item> items;
	int sel_fgc = 0;
	int sel_bgc = 0;
	int ix_selected = 0;
	int ix_first_item = 0;
	int max_visible_items = 0;
};
