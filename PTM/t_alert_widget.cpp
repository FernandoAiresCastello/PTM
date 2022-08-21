#include "t_alert_widget.h"
#include "t_globals.h"
#include "t_panel.h"

t_alert_widget::t_alert_widget(t_globals* g, string title, string text, int fgc, int bgc) {
	wnd = g->wnd;
	buf = g->wnd->GetBuffer(0);
	this->text = text;
	int h = 1;
	int w = g->wnd->GetBuffer(0)->Cols - 6;
	int x = 2;
	int y = (g->wnd->GetBuffer(0)->Rows - 2) / 2;
	pnl = new t_panel(buf, x, y, w, h, fgc, bgc);
	pnl->title = title;
}
t_alert_widget::~t_alert_widget() {
	delete pnl;
}
void t_alert_widget::show() {
	bool running = true;
	while (running) {
		pnl->draw_frame();
		pnl->print(text, 0, 0);
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN || key == SDLK_ESCAPE) {
				running = false;
			}
		}
	}
}
