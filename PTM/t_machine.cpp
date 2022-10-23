#include "t_machine.h"
#include "t_performance_monitor.h"
#include "t_default_gfx.h"
#include "chars.h"
#include "t_layer.h"
#include "t_interpreter.h"

t_machine::t_machine(TBufferedWindow* wnd) {
	this->wnd = wnd;

	tilebufs["default"] = wnd->GetBuffer(0);
	cur_buf = tilebufs["default"];
	cur_buf->ClearAllLayers();

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
	if (show_perfmon && perfmon && wnd) {
		wnd->SetTitle(perfmon->format_info() + String::Format(" | Clock: %i", clock));
	}
	clock++;
}
void t_machine::init_system_vars() {
	// Keyboard key codes
	set_const("$kb.right", SDLK_RIGHT);
	set_const("$kb.left", SDLK_LEFT);
	set_const("$kb.down", SDLK_DOWN);
	set_const("$kb.up", SDLK_UP);
	set_const("$kb.space", SDLK_SPACE);
	set_const("$kb.enter", SDLK_RETURN);
	set_const("$kb.esc", SDLK_ESCAPE);
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
	input_csr.Add(chars::cursor_full, text_color.fg, text_color.bg);
	input_csr.Add(chars::empty, text_color.fg, text_color.bg);

	while (running) {
		cur_buf->Print(empty_str, csr.layer, initial_x, csr.y, text_color.fg, text_color.bg, tile_transparency);
		cur_buf->Print(str, csr.layer, initial_x, csr.y, text_color.fg, text_color.bg, tile_transparency);
		cur_buf->SetTile(input_csr, csr.layer, csr.x, csr.y, tile_transparency);
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

	cur_buf->PutChar(chars::empty, csr.layer, csr.x, csr.y, text_color.fg, text_color.bg, tile_transparency);
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
void t_machine::print_text(string text, bool crlf, bool add_frames) {
	if (text.empty() && crlf) {
		text = "\\n";
	} else if (crlf) {
		text += "\\n";
	}
	const int initial_x = get_csr_x();
	bool escape = false;
	string escape_seq = "";
	int fgc = text_color.fg;
	int bgc = text_color.bg;
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
		} else if (ch == '{') {
			escape = true;
			continue;
		} else if (ch == '}') {
			escape = false;
			if (String::StartsWith(escape_seq, 'c')) {
				string chstr = String::Skip(escape_seq, 1);
				ch = String::ToInt(chstr);
				auto tile = TTileSeq(ch, fgc, bgc);
				if (add_frames) {
					add_tile_frame_at_cursor_pos(tile.Get(0));
				} else {
					put_tile_at_cursor_pos(tile);
				}
				move_cursor(1, 0);
				escape_seq = "";
				continue;
			} else if (String::StartsWith(escape_seq, 'f')) {
				fgc = String::ToInt(String::Skip(escape_seq, 1));
				escape_seq = "";
				continue;
			} else if (String::StartsWith(escape_seq, "/f")) {
				fgc = text_color.fg;
				escape_seq = "";
				continue;
			} else if (String::StartsWith(escape_seq, 'b')) {
				bgc = String::ToInt(String::Skip(escape_seq, 1));
				escape_seq = "";
				continue;
			} else if (String::StartsWith(escape_seq, "/b")) {
				bgc = text_color.bg;
				escape_seq = "";
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
	auto cmd = split_tile_sequence(seq);
	for (int i = 0; i < cmd.size(); i++) {
		auto value = String::ToUpper(cmd[i]);
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
			put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'R')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				put_cur_tile_at_cursor_pos();
				csr.x++;
			}
			put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'L')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				put_cur_tile_at_cursor_pos();
				csr.x--;
			}
			put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'U')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				put_cur_tile_at_cursor_pos();
				csr.y--;
			}
			put_cur_tile_at_cursor_pos();
		} else if (String::StartsWith(value, 'D')) {
			int count = String::ToInt(String::Skip(value, 1));
			for (int i = 0; i < count; i++) {
				put_cur_tile_at_cursor_pos();
				csr.y++;
			}
			put_cur_tile_at_cursor_pos();
		}
	}
}
std::vector<string> t_machine::split_tile_sequence(std::string& seq) {
	seq = String::Trim(seq);
	std::vector<std::string> cmds;
	std::string cmd;

	for (int i = 0; i < seq.size(); i++) {
		char ch = toupper(seq[i]);
		if (isalpha(ch)) {
			if (cmd != "") {
				cmds.push_back(cmd);
				cmd = "";
				i--;
			} else {
				cmd += ch;
			}
		} else if (isdigit(ch)) {
			cmd += ch;
		}
	}
	if (cmd != "") {
		cmds.push_back(cmd);
	}

	return cmds;
}
