#include "t_labels_widget.h"
#include "t_globals.h"
#include "t_list_widget.h"
#include "t_program.h"
#include "t_panel.h"
#include "chars.h"

static int last_ix_selected = 0;

t_labels_widget::t_labels_widget(
    t_globals* g, string title, int x, int y, int w, int h, 
    int fgc, int bgc, int sel_fgc, int sel_bgc) {

    wnd = g->wnd;
    list = new t_list_widget(g, title, 6, 2, 31, 19, fgc, bgc, sel_fgc, sel_bgc);
}
t_labels_widget::~t_labels_widget() {
    last_ix_selected = list->get_selected_index();
    delete list;
}
string t_labels_widget::select_label(t_program* prg) {
    populate_list(prg);
    list->select(last_ix_selected);
    t_list_widget_item* item = list->run_default_selection_loop(SDLK_TAB);
    return item ? item->data : "";
}
void t_labels_widget::populate_list(t_program* prg) {
	list->clear();
	auto labels = prg->labels;
	TTileSeq icon;
	icon.Add(chars::file_icon, list->get_panel()->fgc, list->get_panel()->bgc);
	for (auto& label : labels) {
		list->add_item(label.first, label.first, icon);
	}
    list->sort_alphabetically();
}
