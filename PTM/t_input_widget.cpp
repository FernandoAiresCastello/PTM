#include "t_input_widget.h"
#include "t_globals.h"
#include "t_panel.h"

t_input_widget::t_input_widget(t_globals* g, string title, int fgc, int bgc) : 
	t_input_widget(g, title, "", fgc, bgc) {
}
t_input_widget::t_input_widget(t_globals* g, string title, string text, int fgc, int bgc) :
	t_input_widget(g, title, text, 
		g->wnd->GetBuffer()->Cols - 7, fgc, bgc, 2, (g->wnd->GetBuffer()->Rows - 2) / 2) {
}
t_input_widget::t_input_widget(
	t_globals* g, string title, string text, int maxlen, int fgc, int bgc, int x, int y) {

	wnd = g->wnd;
	buf = g->wnd->GetBuffer();
	this->maxlen = maxlen;
	pnl = new t_panel(buf, x, y, maxlen + 1, 1, fgc, bgc);
	pnl->title = title;
	initial_str = text;
}
t_input_widget::~t_input_widget() {
	delete pnl;
}
string t_input_widget::show() {
	TTileSeq csr;
	csr.Add(0xdb, pnl->bgc, pnl->fgc);
	csr.Add(0xdb, pnl->fgc, pnl->bgc);

	if (initial_str.length() > maxlen) {
		initial_str = initial_str.substr(0, pnl->frame_w);
	}
	string str = initial_str;
	int ix = initial_str.length();
	const int y = 0;
	bool running = true;

	while (running) {
		pnl->draw_frame();
		pnl->print(str, 0, 0);
		pnl->put_tile(csr, ix, y, false);
		wnd->Update();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN) {
				running = false;
			} else if (key == SDLK_ESCAPE) {
				str = initial_str;
				running = false;
			} else if (key == SDLK_BACKSPACE && str.length() > 0) {
				str.pop_back();
				ix--;
			} else if (str.length() < maxlen) {
				if (key >= 0x20 && key < 0x7f) {
					if (TKey::CapsLock()) {
						key = String::ToUpper(key);
					}
					if (TKey::Shift()) {
						key = String::ToUpper(String::ShiftChar(key));
					}
					str.push_back((char)key);
					ix++;
				}
			}
		}
	}
	return String::Trim(str);
}
