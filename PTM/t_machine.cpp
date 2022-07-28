#include "t_machine.h"
#include "t_default_gfx.h"
#include "chars.h"

t_machine::t_machine(TBufferedWindow* wnd) {
	init_system_vars();

	this->wnd = wnd;

	tilebuf = wnd->GetBuffer();
	tilebuf->ClearAllLayers();

	original_chr = wnd->GetCharset();
	chr = new TCharset();
	t_default_gfx::init_charset(chr);
	wnd->SetCharset(chr);

	original_pal = wnd->GetPalette();
	pal = new TPalette();
	t_default_gfx::init_palette(pal);
	wnd->SetPalette(pal);

	set_window_bgcolor(default_bgc);
	wnd->Update();
}
t_machine::~t_machine() {
	wnd->SetCharset(original_chr);
	wnd->SetPalette(original_pal);
	snd->StopMainSound();
	snd->StopSubSound();
	delete chr;
	delete pal;
}
void t_machine::on_loop() {
}
void t_machine::on_screen_update() {
	if (csr.visible) {
		csr.tile.Add(chars::cursor_full, csr.color, csr.color);
		csr.tile.Add(chars::empty, csr.color, csr.color);
		tilebuf->SetTile(csr.tile, PTM_LAYER_TOPMOST, csr.x, csr.y, true);
	}
	wnd->Update();
}
void t_machine::init_system_vars() {
	set_const("sys.layer.btm", PTM_LAYER_BTM);
	set_const("sys.layer.top", PTM_LAYER_TOP);
	set_const("sys.layer.topmost", PTM_LAYER_TOPMOST);
	set_const("sys.panel.layer", PTM_PANEL_LAYER);

	set_const("sys.kb.right", 1073741903);
	set_const("sys.kb.left", 1073741904);
	set_const("sys.kb.down", 1073741905);
	set_const("sys.kb.up", 1073741906);
}
void t_machine::set_var(string id, int value) {
	vars[id] = t_variable(value);
}
void t_machine::set_var(string id, string value) {
	vars[id] = t_variable(value);
}
void t_machine::set_const(string id, int value) {
	vars[id] = t_variable(value, true);
}
void t_machine::set_const(string id, string value) {
	vars[id] = t_variable(value, true);
}
void t_machine::put_cur_tile_at_cursor_pos() {
	tilebuf->SetTile(cur_tile, csr.layer, csr.x, csr.y, tile_transparency);
}
void t_machine::delete_tile_at_cursor_pos() {
	tilebuf->EraseTile(csr.layer, csr.x, csr.y);
}
void t_machine::set_window_bgcolor(int palette_ix) {
	wnd->SetBackColor(pal->GetColorRGB(palette_ix));
}
