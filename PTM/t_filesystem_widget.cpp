#include "t_filesystem_widget.h"
#include "t_list_widget.h"
#include "t_globals.h"
#include "t_panel.h"
#include "chars.h"

int last_ix_selected = 0;

t_filesystem_widget::t_filesystem_widget(
	t_globals* g, string title, int x, int y, int w, int h, 
	int fgc, int bgc, int sel_fgc, int sel_bgc) {

	wnd = g->wnd;
	list = new t_list_widget(g, "Load program", 6, 2, 31, 19, fgc, bgc, sel_fgc, sel_bgc);
}
t_filesystem_widget::~t_filesystem_widget() {
	last_ix_selected = list->get_selected_index();
	delete list;
}
string t_filesystem_widget::select_file(string initial_folder) {
	if (initial_folder.empty()) initial_folder = ".";
	populate_list(initial_folder);
	list->select(last_ix_selected);
	string path = "";
	while (true) {
		list->draw();
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			break;
		} else if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_ESCAPE) {
				path = "";
				break;
			} else if (key == SDLK_RETURN) {
				path = list->get_selected_item().data;
				break;
			} else if (key == SDLK_DOWN) {
				list->select_next();
			} else if (key == SDLK_UP) {
				list->select_prev();
			}
		}
	}
	return path;
}
void t_filesystem_widget::populate_list(string folder) {
	list->clear();
	auto files = File::List(folder, "", false);
	TTileSeq icon;
	icon.Add(chars::file_icon, list->get_panel()->fgc, list->get_panel()->bgc);
	for (auto& file : files) {
		if (String::EndsWith(file, '.ptm')) {
			string path = folder + "\\" + file;
			list->add_item(file, path, icon);
		}
	}
}
