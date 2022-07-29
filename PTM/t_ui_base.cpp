#include "t_ui_base.h"
#include "t_globals.h"
#include "t_config.h"
#include "t_default_gfx.h"
#include "chars.h"
#include "t_layer.h"

t_ui_base::t_ui_base(t_globals* g) {
	globals = g;
	cfg = g->cfg;
	wnd = g->wnd;
	buf = g->wnd->GetBuffer();
	snd = g->snd;
	running = false;
	t_default_gfx::init_palette(wnd->GetPalette());
	t_default_gfx::init_charset(wnd->GetCharset());

	color.fg = 255;
	color.bg = 254;
	color.bdr_fg = 253;
	color.bdr_bg = 252;
	color.label_fg = 251;
	color.cmd_fg = 250;
	color.csr_fg = 249;
	color.comment_fg = 248;
	color.sel_bg = 247;
	color.fg_bold = 246;
	color.error_bg = 245;
	color.pnl_bg = 244;
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
		if (on_exit()) {
			running = false;
		}
	} else if (e.type == SDL_KEYDOWN) {
		auto key = e.key.keysym.sym;
		if (TKey::Alt() && key == SDLK_RETURN) {
			wnd->ToggleFullscreen();
		} else {
			on_keydown(key, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		}
	} else if (e.type == SDL_MOUSEWHEEL) {
		on_mouse_wheel(-e.wheel.y);
	}
}
void t_ui_base::draw_screen_base() {
	wnd->SetBackColor(wnd->GetPalette()->GetColorRGB(color.bg));
	buf->ClearAllLayers();
	draw_border();
}
void t_ui_base::draw_border() {
	TTileSeq tile(chars::empty, color.bdr_bg, color.bdr_bg);
	for (int y = 0; y < buf->Rows; y++) {
		buf->SetTile(tile, t_layer::bottom, 0, y, false);
		buf->SetTile(tile, t_layer::bottom, buf->LastCol, y, false);
	}
	for (int x = 0; x < buf->Cols; x++) {
		buf->SetTile(tile, t_layer::bottom, x, 0, false);
		buf->SetTile(tile, t_layer::bottom, x, buf->LastRow, false);
	}
}
void t_ui_base::print_border(string str, int top_or_bottom, int x) {
	int px = x + 1;
	int y = top_or_bottom > 0 ? buf->LastRow : 0;
	for (auto& ch : str) {
		buf->SetTile(TTileSeq(ch, color.bdr_fg, color.bdr_bg), t_layer::bottom, px++, y, false);
	}
}
void t_ui_base::print_border_top(string str, int x) {
	print_border(str, 0, x);
}
void t_ui_base::print_border_bottom(string str, int x) {
	print_border(str, 1, x);
}
