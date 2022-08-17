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

	csr.tile.AddBlank(2);

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
	if (wnd && perfmon) wnd->SetTitle(perfmon->format_info() + 
		String::Format(" | Clock: %i", clock));

	clock++;
}
void t_machine::on_screen_update() {
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
	// Keyboard codes
	set_const("$kb.right", SDL_SCANCODE_RIGHT);
	set_const("$kb.left", SDL_SCANCODE_LEFT);
	set_const("$kb.down", SDL_SCANCODE_DOWN);
	set_const("$kb.up", SDL_SCANCODE_UP);
	set_const("$kb.enter", SDL_SCANCODE_RETURN);
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
void t_machine::put_tile_at_cursor_pos(TTileSeq& tile) {
	tilebuf->SetTile(tile, csr.layer, csr.x, csr.y, tile_transparency);
}
void t_machine::put_cur_tile_at_cursor_pos() {
	tilebuf->SetTile(cur_tile, csr.layer, csr.x, csr.y, tile_transparency);
}
void t_machine::copy_tile_at_cursor_pos() {
	if (csr.x >= 0 && csr.y >= 0 && csr.x < tilebuf->Cols && csr.y < tilebuf->Rows) {
		cur_tile = tilebuf->GetTile(csr.layer, csr.x, csr.y);
	}
}
void t_machine::delete_tile_at_cursor_pos() {
	tilebuf->EraseTile(csr.layer, csr.x, csr.y);
}
void t_machine::set_window_bgcolor(int palette_ix) {
	wnd->SetBackColor(pal->GetColorRGB(palette_ix));
}
void t_machine::set_cursor_pos(int x, int y) {
	csr.x = x;
	csr.y = y;
}
void t_machine::move_cursor(int dx, int dy) {
	csr.x += dx;
	csr.y += dy;
}
int t_machine::get_csr_layer() {
	return csr.layer;
}
int t_machine::get_csr_x() {
	return csr.x;
}
int t_machine::get_csr_y() {
	return csr.y;
}
void t_machine::set_csr_layer(int layer) {
	csr.layer = layer;
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
string t_machine::read_input_string(int maxlen) {
	string str = "";
	string empty_str = string(maxlen + 1, ' ');
	const int initial_x = csr.x;
	const int y = 0;
	int ix = 0;
	bool running = true;

	TTileSeq input_csr;
	input_csr.Add(chars::cursor_full, text_color.fg, text_color.bg);
	input_csr.Add(chars::empty, text_color.fg, text_color.bg);

	while (running) {
		tilebuf->Print(empty_str, csr.layer, initial_x, csr.y, text_color.fg, text_color.bg, tile_transparency);
		tilebuf->Print(str, csr.layer, initial_x, csr.y, text_color.fg, text_color.bg, tile_transparency);
		tilebuf->SetTile(input_csr, csr.layer, csr.x, csr.y, tile_transparency);
		wnd->Update();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN) {
				if (TKey::Alt()) wnd->ToggleFullscreen();
				else running = false;
			} else if (key == SDLK_ESCAPE) {
				str = "";
				running = false;
			} else if (key == SDLK_BACKSPACE && str.length() > 0) {
				str.pop_back();
				ix--;
				csr.x--;
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
					csr.x++;
				}
			}
		}
	}

	tilebuf->PutChar(chars::empty, csr.layer, csr.x, csr.y, text_color.fg, text_color.bg, tile_transparency);
	return str;
}
