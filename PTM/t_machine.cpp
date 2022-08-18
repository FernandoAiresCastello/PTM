#include "t_machine.h"
#include "t_performance_monitor.h"
#include "t_default_gfx.h"
#include "chars.h"
#include "t_layer.h"
#include "t_interpreter.h"

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
std::vector<string> t_machine::get_debug_info() {
	std::vector<string> info;
	// Variables
	info.push_back("Variables");
	if (vars.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& var : vars) {
		info.push_back(
			(var.second.is_const ? "\tconst " : "\t") +
			String::Format("%s = %s", var.first.c_str(), var.second.value.c_str()));
	}
	info.push_back("");
	// Arrays
	info.push_back("Arrays");
	if (arrays.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& arr_inst : arrays) {
		string id = arr_inst.first;
		auto& arr = arr_inst.second;
		info.push_back(String::Format("\t%s (length=%i)", id.c_str(), arr.size()));
		for (int i = 0; i < arr.size(); i++) {
			info.push_back(String::Format("\t\t[%i] = %s", i, arr[i].c_str()));
		}
	}
	info.push_back("");
	// Tilestore
	info.push_back("Tilestore");
	if (tilestore.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& saved_tile : tilestore) {
		string id = saved_tile.first;
		string tile = saved_tile.second.ToString();
		info.push_back(String::Format("\t%s = %s", id.c_str(), tile.c_str()));
	}
	info.push_back("");
	// Current tile
	info.push_back("Current tile");
	if (cur_tile.IsEmpty()) {
		info.push_back("\t(empty)");
	} else {
		info.push_back(String::Format("\t%s", cur_tile.ToString().c_str()));
	}
	info.push_back("");
	// Tile buffer cursor
	info.push_back("Tile buffer cursor");
	info.push_back(String::Format("\tLayer=%i X=%i Y=%i",
		get_csr_layer(), get_csr_x(), get_csr_y()));
	info.push_back("");
	// Callstack
	info.push_back("Callstack");
	if (intp->callstack.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& prg_ix : intp->callstack._Get_container()) {
		info.push_back("\t" + String::ToString(prg_ix));
	}
	return info;
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
void t_machine::move_tile_at_cursor_pos(int dx, int dy) {
	TTileSeq tile = tilebuf->GetTile(csr.layer, csr.x, csr.y);
	tilebuf->EraseTile(csr.layer, csr.x, csr.y);
	tilebuf->SetTile(tile, csr.layer, csr.x + dx, csr.y + dy, tile_transparency);
}
void t_machine::move_tile_block(int x, int y, int w, int h, int dx, int dy) {
	std::vector<TTileSeq> tiles;
	for (int cy = y; cy < y + h; cy++) {
		for (int cx = x; cx < x + w; cx++) {
			if (cx >= 0 && cy >= 0 && cx < tilebuf->Cols && cy < tilebuf->Rows) {
				tiles.push_back(tilebuf->GetTile(csr.layer, cx, cy));
				tilebuf->EraseTile(csr.layer, cx, cy);
			} else {
				tiles.push_back(TTileSeq());
			}
		}
	}
	const int new_x = x + dx;
	const int new_y = y + dy;
	int i = 0;
	for (int cy = new_y; cy < new_y + h; cy++) {
		for (int cx = new_x; cx < new_x + w; cx++) {
			tilebuf->SetTile(tiles[i++], csr.layer, cx, cy, tile_transparency);
		}
	}
}
