#include "t_machine.h"
#include "t_performance_monitor.h"
#include "t_default_gfx.h"
#include "t_interpreter.h"

#define KBMAP(x,y) kbmap[x] = y;

t_machine::t_machine(TBufferedWindow* wnd) {
	this->wnd = wnd;
	wnd->RemoveAllBuffersExceptDefault();

	cur_buf_id = "default";
	tilebufs[cur_buf_id] = wnd->GetBuffer(0);
	cur_buf = tilebufs[cur_buf_id];
	cur_buf->ClearAllLayers();

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
	init_keyboard_map();
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
	if (show_perfmon && perfmon && wnd) {
		wnd->SetTitle(perfmon->format_info() + String::Format(" | Clock: %i", clock));
	}
	clock++;
}
void t_machine::init_system_vars() {
}
void t_machine::init_keyboard_map() {
	KBMAP("RIGHT", SDL_SCANCODE_RIGHT);
	KBMAP("LEFT", SDL_SCANCODE_LEFT);
	KBMAP("UP", SDL_SCANCODE_UP);
	KBMAP("DOWN", SDL_SCANCODE_DOWN);
	KBMAP("SPACE", SDL_SCANCODE_SPACE);
	KBMAP("ENTER", SDL_SCANCODE_RETURN);
	KBMAP("ESC", SDL_SCANCODE_ESCAPE);
	KBMAP("TAB", SDL_SCANCODE_TAB);
	KBMAP("BS", SDL_SCANCODE_BACKSPACE);
	KBMAP("INS", SDL_SCANCODE_INSERT);
	KBMAP("DEL", SDL_SCANCODE_DELETE);
	KBMAP("HOME", SDL_SCANCODE_HOME);
	KBMAP("END", SDL_SCANCODE_END);
	KBMAP("PGUP", SDL_SCANCODE_PAGEUP);
	KBMAP("PGDN", SDL_SCANCODE_PAGEDOWN);
	KBMAP("F1", SDL_SCANCODE_F1);
	KBMAP("F2", SDL_SCANCODE_F2);
	KBMAP("F3", SDL_SCANCODE_F3);
	KBMAP("F4", SDL_SCANCODE_F4);
	KBMAP("F5", SDL_SCANCODE_F5);
	KBMAP("F6", SDL_SCANCODE_F6);
	KBMAP("F7", SDL_SCANCODE_F7);
	KBMAP("F8", SDL_SCANCODE_F8);
	KBMAP("F9", SDL_SCANCODE_F9);
	KBMAP("F10", SDL_SCANCODE_F10);
	KBMAP("F11", SDL_SCANCODE_F11);
	KBMAP("F12", SDL_SCANCODE_F12);
	KBMAP("A", SDL_SCANCODE_A);
	KBMAP("B", SDL_SCANCODE_B);
	KBMAP("C", SDL_SCANCODE_C);
	KBMAP("D", SDL_SCANCODE_D);
	KBMAP("E", SDL_SCANCODE_E);
	KBMAP("F", SDL_SCANCODE_F);
	KBMAP("G", SDL_SCANCODE_G);
	KBMAP("H", SDL_SCANCODE_H);
	KBMAP("I", SDL_SCANCODE_I);
	KBMAP("J", SDL_SCANCODE_J);
	KBMAP("K", SDL_SCANCODE_K);
	KBMAP("L", SDL_SCANCODE_L);
	KBMAP("M", SDL_SCANCODE_M);
	KBMAP("N", SDL_SCANCODE_N);
	KBMAP("O", SDL_SCANCODE_O);
	KBMAP("P", SDL_SCANCODE_P);
	KBMAP("Q", SDL_SCANCODE_Q);
	KBMAP("R", SDL_SCANCODE_R);
	KBMAP("S", SDL_SCANCODE_S);
	KBMAP("T", SDL_SCANCODE_T);
	KBMAP("U", SDL_SCANCODE_U);
	KBMAP("V", SDL_SCANCODE_V);
	KBMAP("W", SDL_SCANCODE_W);
	KBMAP("X", SDL_SCANCODE_X);
	KBMAP("Y", SDL_SCANCODE_Y);
	KBMAP("Z", SDL_SCANCODE_Z);
	KBMAP("0", SDL_SCANCODE_0);
	KBMAP("1", SDL_SCANCODE_1);
	KBMAP("2", SDL_SCANCODE_2);
	KBMAP("3", SDL_SCANCODE_3);
	KBMAP("4", SDL_SCANCODE_4);
	KBMAP("5", SDL_SCANCODE_5);
	KBMAP("6", SDL_SCANCODE_6);
	KBMAP("7", SDL_SCANCODE_7);
	KBMAP("8", SDL_SCANCODE_8);
	KBMAP("9", SDL_SCANCODE_9);
}
string t_machine::get_keyname(SDL_Keycode key) {
	if (key == 0) return "NONE";
	if (key == SDLK_RIGHT) return "RIGHT";
	if (key == SDLK_LEFT) return "LEFT";
	if (key == SDLK_UP) return "UP";
	if (key == SDLK_DOWN) return "DOWN";
	if (key == SDLK_SPACE) return "SPACE";
	if (key == SDLK_RETURN) return "ENTER";
	if (key == SDLK_ESCAPE) return "ESC";
	if (key == SDLK_TAB) return "TAB";
	if (key == SDLK_BACKSPACE) return "BS";
	if (key == SDLK_INSERT) return "INS";
	if (key == SDLK_DELETE) return "DEL";
	if (key == SDLK_HOME) return "HOME";
	if (key == SDLK_END) return "END";
	if (key == SDLK_PAGEUP) return "PGUP";
	if (key == SDLK_PAGEDOWN) return "PGDN";
	if (key == SDLK_CAPSLOCK) return "CAPS";
	if (key == SDLK_LSHIFT || key == SDLK_RSHIFT) return "SHIFT";
	if (key == SDLK_LCTRL || key == SDLK_RCTRL) return "CTRL";
	if (key == SDLK_RALT || key == SDLK_LALT) return "ALT";
	if (key == SDLK_F1) return "F1";
	if (key == SDLK_F2) return "F2";
	if (key == SDLK_F3) return "F3";
	if (key == SDLK_F4) return "F4";
	if (key == SDLK_F5) return "F5";
	if (key == SDLK_F6) return "F6";
	if (key == SDLK_F7) return "F7";
	if (key == SDLK_F8) return "F8";
	if (key == SDLK_F9) return "F9";
	if (key == SDLK_F10) return "F10";
	if (key == SDLK_F11) return "F11";
	if (key == SDLK_F12) return "F12";
	if (key == SDLK_a) return "A";
	if (key == SDLK_b) return "B";
	if (key == SDLK_c) return "C";
	if (key == SDLK_d) return "D";
	if (key == SDLK_e) return "E";
	if (key == SDLK_f) return "F";
	if (key == SDLK_g) return "G";
	if (key == SDLK_h) return "H";
	if (key == SDLK_i) return "I";
	if (key == SDLK_j) return "J";
	if (key == SDLK_k) return "K";
	if (key == SDLK_l) return "L";
	if (key == SDLK_m) return "M";
	if (key == SDLK_n) return "N";
	if (key == SDLK_o) return "O";
	if (key == SDLK_p) return "P";
	if (key == SDLK_q) return "Q";
	if (key == SDLK_r) return "R";
	if (key == SDLK_s) return "S";
	if (key == SDLK_t) return "T";
	if (key == SDLK_u) return "U";
	if (key == SDLK_v) return "V";
	if (key == SDLK_w) return "W";
	if (key == SDLK_x) return "X";
	if (key == SDLK_y) return "Y";
	if (key == SDLK_z) return "Z";
	if (key == SDLK_0) return "0";
	if (key == SDLK_1) return "1";
	if (key == SDLK_2) return "2";
	if (key == SDLK_3) return "3";
	if (key == SDLK_4) return "4";
	if (key == SDLK_5) return "5";
	if (key == SDLK_6) return "6";
	if (key == SDLK_7) return "7";
	if (key == SDLK_8) return "8";
	if (key == SDLK_9) return "9";
	return String::ToString(key);
}
std::vector<string> t_machine::get_debug_info() {
	std::vector<string> info;
	// Variables
	info.push_back("Variables");
	if (vars.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& var : vars) {
		if (!var.second.is_const) {
			info.push_back(String::Format("\t%s = %s", var.first.c_str(), var.second.value.c_str()));
		}
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
	// Tile buffers
	info.push_back("Tile buffers");
	info.push_back(String::Format("\tCursor: Layer=%i X=%i Y=%i",
		get_csr_layer(), get_csr_x(), get_csr_y()));
	for (auto& buf : tilebufs) {
		info.push_back(String::Format("\t%s (w=%i h=%i layers=%i)", 
			buf.first.c_str(), buf.second->Cols, buf.second->Rows, buf.second->LayerCount));
	}
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
void t_machine::save_debug_file() {
	File::WriteLines(PTM_DEBUG_FILE, get_debug_info());
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
	cur_buf->SetTile(tile, csr.layer, csr.x, csr.y, tile_transparency);
}
void t_machine::add_tile_frame_at_cursor_pos(TTile& tile) {
	if (csr.x >= 0 && csr.y >= 0 && csr.x < cur_buf->Cols && csr.y < cur_buf->Rows) {
		cur_buf->GetTile(csr.layer, csr.x, csr.y).Add(tile);
	}
}
void t_machine::put_cur_tile_at_cursor_pos() {
	cur_buf->SetTile(cur_tile, csr.layer, csr.x, csr.y, tile_transparency);
}
void t_machine::copy_tile_at_cursor_pos() {
	if (csr.x >= 0 && csr.y >= 0 && csr.x < cur_buf->Cols && csr.y < cur_buf->Rows) {
		cur_tile = cur_buf->GetTile(csr.layer, csr.x, csr.y);
	}
}
void t_machine::delete_tile_at_cursor_pos() {
	cur_buf->EraseTile(csr.layer, csr.x, csr.y);
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
	input_csr.Add(0x00, text_color.bg, text_color.fg);
	input_csr.Add(0x00, text_color.fg, text_color.bg);

	while (running && intp->running) {
		cur_buf->Print(empty_str, csr.layer, initial_x, csr.y, text_color.fg, text_color.bg, tile_transparency);
		cur_buf->Print(str, csr.layer, initial_x, csr.y, text_color.fg, text_color.bg, tile_transparency);
		cur_buf->SetTile(input_csr, csr.layer, csr.x, csr.y, false);
		wnd->Update();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN) {
				if (TKey::Alt() || TKey::Shift() || TKey::Ctrl()) {
					intp->process_global_keypress(key);
				} else {
					running = false;
				}
			} else if (key == SDLK_ESCAPE) {
				str = "";
				running = false;
			} else if (key == SDLK_BACKSPACE && str.length() > 0) {
				str.pop_back();
				ix--;
				csr.x--;
			} else if (key == SDLK_PAUSE || key == SDLK_PRINTSCREEN) {
				intp->process_global_keypress(key);
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

	cur_buf->PutChar(0x00, csr.layer, csr.x, csr.y, text_color.fg, text_color.bg, tile_transparency);
	return str;
}
void t_machine::move_tile_at_cursor_pos(int dx, int dy) {
	TTileSeq tile = cur_buf->GetTile(csr.layer, csr.x, csr.y);
	cur_buf->EraseTile(csr.layer, csr.x, csr.y);
	cur_buf->SetTile(tile, csr.layer, csr.x + dx, csr.y + dy, tile_transparency);
}
void t_machine::move_tile_block(int x, int y, int w, int h, int dx, int dy) {
	std::vector<TTileSeq> tiles;
	for (int cy = y; cy < y + h; cy++) {
		for (int cx = x; cx < x + w; cx++) {
			if (cx >= 0 && cy >= 0 && cx < cur_buf->Cols && cy < cur_buf->Rows) {
				tiles.push_back(cur_buf->GetTile(csr.layer, cx, cy));
				cur_buf->EraseTile(csr.layer, cx, cy);
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
			cur_buf->SetTile(tiles[i++], csr.layer, cx, cy, tile_transparency);
		}
	}
}
void t_machine::print_text(string text, bool crlf, bool add_frames, bool raw) {
	print_text(text, crlf, add_frames, text_color.fg, text_color.bg, raw);
}
void t_machine::print_text(string text, bool crlf, bool add_frames, int fgc, int bgc, bool raw) {
	if (text.empty() && crlf) {
		text = "\\n";
	} else if (crlf) {
		text += "\\n";
	}
	const int initial_x = get_csr_x();
	bool escape = false;
	string escape_seq = "";
	for (int i = 0; i < text.length(); i++) {
		int ch = text[i];
		if (ch == '\\') {
			i++;
			if (i < text.length()) {
				if (text[i] == 'n') {
					move_cursor(0, 1);
					set_cursor_pos(initial_x, get_csr_y());
				}
			}
		} else if (!raw && ch == '{') {
			escape = true;
			continue;
		} else if (!raw && ch == '}') {
			escape = false;
			const string upper_escape_seq = String::ToUpper(escape_seq);
			if (String::StartsWith(upper_escape_seq, 'C')) {
				ch = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
				auto tile = TTileSeq(ch, fgc, bgc);
				if (add_frames) {
					add_tile_frame_at_cursor_pos(tile.Get(0));
				} else {
					put_tile_at_cursor_pos(tile);
				}
				move_cursor(1, 0);
				escape_seq = "";
				continue;
			} else if (String::StartsWith(upper_escape_seq, 'F')) {
				fgc = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
				escape_seq = "";
				continue;
			} else if (String::StartsWith(upper_escape_seq, "/F")) {
				fgc = text_color.fg;
				escape_seq = "";
				continue;
			} else if (String::StartsWith(upper_escape_seq, 'B')) {
				bgc = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
				escape_seq = "";
				continue;
			} else if (String::StartsWith(upper_escape_seq, "/B")) {
				bgc = text_color.bg;
				escape_seq = "";
				continue;
			} else if (String::StartsWith(escape_seq, '%')) {
				string var = String::Skip(escape_seq, 1);
				escape_seq = "";
				print_text(vars[var].value, false, false, fgc, bgc, true);
				continue;
			} else {
				intp->abort("Invalid escape sequence: " + escape_seq);
			}
		} else if (escape) {
			escape_seq += ch;
			continue;
		} else {
			auto tile = TTileSeq(ch, fgc, bgc);
			if (add_frames) {
				add_tile_frame_at_cursor_pos(tile.Get(0));
			} else {
				put_tile_at_cursor_pos(tile);
			}
			move_cursor(1, 0);
			escape_seq = "";
		}
	}
}
void t_machine::draw_tile_sequence(string seq) {
	if (cur_tile.IsEmpty()) {
		cur_tile.AddBlank();
	}
	bool draw = false;
	auto cmd = String::Split(seq, ' ', true);
	for (int i = 0; i < cmd.size(); i++) {
		auto value = String::ToUpper(cmd[i]);
		value = String::Replace(value, "&H", "0x");
		if (String::StartsWith(value, 'F')) {
			cur_tile.SetForeColor(0, String::ToInt(String::Skip(value, 1)));
		} else if (String::StartsWith(value, 'B')) {
			cur_tile.SetBackColor(0, String::ToInt(String::Skip(value, 1)));
		} else if (String::StartsWith(value, 'C')) {
			cur_tile.SetChar(0, String::ToInt(String::Skip(value, 1)));
		} else if (String::StartsWith(value, 'X')) {
			csr.x = String::ToInt(String::Skip(value, 1));
		} else if (String::StartsWith(value, 'Y')) {
			csr.y = String::ToInt(String::Skip(value, 1));
		} else if (String::StartsWith(value, 'P')) {
			draw = true;
			put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'M')) {
			draw = false;
			put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'R')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				if (draw) put_cur_tile_at_cursor_pos();
				csr.x++;
			}
			if (draw) put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'L')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				if (draw) put_cur_tile_at_cursor_pos();
				csr.x--;
			}
			if (draw) put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'U')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				if (draw) put_cur_tile_at_cursor_pos();
				csr.y--;
			}
			if (draw) put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'D')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				if (draw) put_cur_tile_at_cursor_pos();
				csr.y++;
			}
			if (draw) put_cur_tile_at_cursor_pos();
		}
	}
}
bool t_machine::is_key_pressed(string keyname) {
	keyname = String::ToUpper(keyname);
	
	if (keyname == "SHIFT") return TKey::Shift();
	if (keyname == "CTRL") return TKey::Ctrl();
	if (keyname == "ALT") return TKey::Alt();
	if (keyname == "CAPS") return TKey::CapsLock();

	return TKey::IsPressed(kbmap[keyname]);
}
void t_machine::on_key_pressed(SDL_Keycode key) {
	last_keycode_pressed = key;
}
