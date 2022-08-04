#include "t_list_widget.h"
#include "t_globals.h"
#include "t_panel.h"

t_list_widget::t_list_widget(
	t_globals* g, string title, int x, int y, int w, int h, 
	int fgc, int bgc, int sel_fgc, int sel_bgc) {

	wnd = g->wnd;
	buf = g->wnd->GetBuffer();
	pnl = new t_panel(buf, x, y, w, h, fgc, bgc);
	pnl->title = title;
	max_visible_items = h;
	this->sel_fgc = sel_fgc;
	this->sel_bgc = sel_bgc;
}
t_list_widget::~t_list_widget() {
	delete pnl;
}
void t_list_widget::add_item(t_list_widget_item item) {
	items.push_back(item);
}
void t_list_widget::add_item(string text, string data, TTileSeq icon) {
	t_list_widget_item item;
	item.icon = icon;
	item.text = text;
	item.data = data;
	add_item(item);
}
void t_list_widget::clear() {
	items.clear();
}
void t_list_widget::draw() {
	pnl->draw_frame();
	const string padding_right = string(pnl->frame_w, 0);
	int y = 0;
	for (int i = ix_first_item; i < ix_first_item + max_visible_items && i < items.size(); i++) {
		int x = 0;
		const int fgc = i == ix_selected ? sel_fgc : pnl->fgc;
		const int bgc = i == ix_selected ? sel_bgc : pnl->bgc;
		auto& item = items[i];
		for (int i = 0; i < item.icon.GetSize(); i++) {
			item.icon.SetBackColor(i, bgc);
		}
		if (!item.icon.IsEmpty()) {
			pnl->put_tile(item.icon, x, y, false);
			x++;
		}
		pnl->print(" " + item.text + padding_right, x, y, fgc, bgc);
		y++;
	}
}
void t_list_widget::select(int index) {
	ix_selected = index;
}
void t_list_widget::select_next() {
	if (ix_selected >= items.size() - 1) return;
	ix_selected++;
}
void t_list_widget::select_prev() {
	if (ix_selected <= 0) return;
	ix_selected--;
}
void t_list_widget::reset_selection() {
	ix_selected = 0;
	ix_first_item = 0;
}
t_list_widget_item& t_list_widget::get_selected_item() {
	return items[ix_selected];
}
int t_list_widget::get_selected_index() {
	return ix_selected;
}
t_panel* t_list_widget::get_panel() {
	return pnl;
}
