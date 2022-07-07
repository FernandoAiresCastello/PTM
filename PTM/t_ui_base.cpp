#include "t_ui_base.h"
#include "t_globals.h"
#include "t_config.h"

t_ui_base::t_ui_base(t_globals* g) {
	wnd = g->wnd;
	buf = g->wnd->GetBuffer();
	snd = g->snd;
	running = false;
	color.fg = g->cfg->fg_color;
	color.bg = g->cfg->bg_color;
	color.bdr_fg = g->cfg->bdr_fg_color;
	color.bdr_bg = g->cfg->bdr_bg_color;
}
t_ui_base::~t_ui_base() {
}
void t_ui_base::run() {
	running = true;
	while (running) {
		on_run_loop();
		wnd->Update();
		poll_events();
	}
}
void t_ui_base::poll_events() {
	SDL_Event e = { 0 };
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		running = false;
	} else if (e.type == SDL_KEYDOWN) {
		auto key = e.key.keysym.sym;
		if (TKey::Alt() && key == SDLK_RETURN) {
			wnd->ToggleFullscreen();
		} else {
			on_keydown(key, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		}
	}
}
void t_ui_base::draw_screen_base() {
	wnd->SetBackColor(wnd->GetPalette()->GetColorRGB(color.bg));
	buf->ClearAllLayers();
	draw_border();
}
void t_ui_base::draw_border() {
	TTileSeq tile(0, color.bdr_bg, color.bdr_bg);
	for (int y = 0; y < buf->Rows; y++) {
		buf->SetTile(tile, 0, 0, y, false);
		buf->SetTile(tile, 0, buf->LastCol, y, false);
	}
	for (int x = 0; x < buf->Cols; x++) {
		buf->SetTile(tile, 0, x, 0, false);
		buf->SetTile(tile, 0, x, buf->LastRow, false);
	}
}
void t_ui_base::print_border(string str, int top_or_bottom, int x) {
	int px = x + 1;
	int y = top_or_bottom > 0 ? buf->LastRow : 0;
	for (auto& ch : str) {
		buf->SetTile(TTileSeq(ch, color.bdr_fg, color.bdr_bg), 0, px++, y, false);
	}
}
void t_ui_base::print_border_top(string str, int x) {
	print_border(str, 0, x);
}
void t_ui_base::print_border_bottom(string str, int x) {
	print_border(str, 1, x);
}
