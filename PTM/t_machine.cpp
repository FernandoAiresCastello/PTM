#include "t_machine.h"
#include "t_performance_monitor.h"
#include "t_default_gfx.h"
#include "chars.h"
#include "t_layer.h"

t_machine::t_machine(TBufferedWindow* wnd) {
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

	init_system_vars();
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
	if (wnd && perfmon) wnd->SetTitle(perfmon->format_info());
}
void t_machine::on_screen_update() {
	draw_cursor();
	wnd->Update();
}
void t_machine::init_system_vars() {
	// Tile buffer dimensions
	set_const("$scr.cols", tilebuf->Cols);
	set_const("$scr.rows", tilebuf->Rows);
	// Tile buffer layers
	set_const("$layer.btm", t_layer::bottom);
	set_const("$layer.top", t_layer::top);
	set_const("$layer.topmost", t_layer::topmost);
	set_const("$layer.panel", t_layer::panel);
	// Keyboard codes
	set_const("$kb.right", 1073741903);
	set_const("$kb.left", 1073741904);
	set_const("$kb.down", 1073741905);
	set_const("$kb.up", 1073741906);
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
void t_machine::copy_tile_at_cursor_pos() {
	cur_tile = tilebuf->GetTile(csr.layer, csr.x, csr.y);
}
void t_machine::delete_tile_at_cursor_pos() {
	tilebuf->EraseTile(csr.layer, csr.x, csr.y);
}
void t_machine::set_window_bgcolor(int palette_ix) {
	wnd->SetBackColor(pal->GetColorRGB(palette_ix));
}
void t_machine::draw_cursor() {
	if (!csr.visible) return;
	csr.tile.Add(chars::cursor_full, csr.color, csr.color);
	csr.tile.Add(chars::empty, csr.color, csr.color);
	tilebuf->SetTile(csr.tile, t_layer::topmost, csr.x, csr.y, true);
}
void t_machine::erase_cursor() {
	tilebuf->EraseTile(t_layer::topmost, csr.x, csr.y);
}
bool t_machine::is_valid_tileseq(TTileSeq& tileseq) {
	bool valid = true;
	for (int i = 0; i < tileseq.GetSize(); i++) {
		if (!is_valid_tile(tileseq.Get(i))) {
			valid = false;
			break;
		}
	}
	return valid;
}
bool t_machine::is_valid_tile(const TTile& tile) {
	return
		tile.Char >= 0 && tile.Char < chr->GetSize() &&
		tile.ForeColor >= 0 && tile.ForeColor < pal->GetSize() &&
		tile.BackColor >= 0 && tile.BackColor < pal->GetSize();
}
bool t_machine::is_valid_charset_ix(int ix) {
	return ix >= 0 && ix < chr->GetSize();
}
bool t_machine::is_valid_palette_ix(int ix) {
	return ix >= 0 && ix < pal->GetSize();
}
bool t_machine::is_valid_char_def(int row_ix, int data) {
	return
		row_ix >= 0 && row_ix < TChar::Height &&
		data >= 0 && data < 256;
}
bool t_machine::is_valid_color_rgb(int rgb) {
	return rgb >= 0 && rgb <= 0xffffff;
}
