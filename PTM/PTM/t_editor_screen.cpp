#include "t_editor_screen.h"

#define LAYER_0 0
#define LAYER_1 1

t_editor_screen::t_editor_screen(TBufferedWindow* wnd) {
	this->wnd = wnd;
	buf = wnd->GetBuffer();
	cols = buf->Cols;
	rows = buf->Rows;
	csr.x = 0;
	csr.y = 0;
	color.fg = 15;
	color.bg = 0;
	color.bdr = 5;
}
void t_editor_screen::clear() {
	buf->ClearAllLayers();
	set_cursor(0, 0);
}
void t_editor_screen::set_cursor(int x, int y) {
	buf->EraseTile(LAYER_1, csr.x + 1, csr.y + 1);
	csr.x = x;
	csr.y = y;
}
void t_editor_screen::move_cursor(int dx, int dy) {
	set_cursor(csr.x + dx, csr.y + dy);
}
int t_editor_screen::get_cursor_x() {
	return csr.x;
}
int t_editor_screen::get_cursor_y() {
	return csr.y;
}
TTileSeq& t_editor_screen::get_tile_under_cursor() {
	return buf->GetTile(LAYER_0, csr.x + 1, csr.y + 1);
}
TTileSeq& t_editor_screen::get_tile_at(int x, int y) {
	return buf->GetTile(LAYER_0, x + 1, y + 1);
}
void t_editor_screen::delete_tile_under_cursor() {
	get_tile_under_cursor().Clear();
}
void t_editor_screen::shift_line_from_cursor() {
	string chars;
	int y = csr.y + 1;
	for (int x = csr.x + 2; x < cols; x++) {
		auto tile = buf->GetTile(LAYER_0, x, y);
		if (tile.IsEmpty()) {
			chars += ' ';
		} else {
			chars += tile.GetChar(0);
		}
	}
	print_keep_cursor(chars);
}
string t_editor_screen::get_line_string_at_cursor() {
	string line;
	for (int x = 0; x < cols - 1; x++) {
		auto& tile = get_tile_at(x, csr.y);
		if (!tile.IsEmpty()) {
			int chr = tile.GetChar(0);
			if (chr >= 0x20 && chr < 0x7f) {
				line += chr;
			} else {
				line += ' ';
			}
		} else {
			line += ' ';
		}
	}
	return String::Trim(line);
}
void t_editor_screen::set_colors(int fg, int bg, int bdr) {
	color.fg = fg;
	color.bg = bg;
	color.bdr = bdr;
}
void t_editor_screen::draw_border() {
	TTileSeq tile(0, color.fg, color.bdr);
	for (int x = 0; x < buf->Cols; x++) {
		buf->SetTile(tile, LAYER_0, x, 0, false);
		buf->SetTile(tile, LAYER_0, x, buf->LastRow, false);
	}
	for (int y = 0; y < buf->Rows; y++) {
		buf->SetTile(tile, LAYER_0, 0, y, false);
		buf->SetTile(tile, LAYER_0, buf->LastCol, y, false);
	}
}
void t_editor_screen::draw_cursor() {
	csr.tile.Clear();
	auto& under = get_tile_under_cursor();
	if (!under.IsEmpty()) {
		csr.tile.Add(under.GetChar(0), color.bg, color.fg);
		csr.tile.Add(under.GetChar(0), color.fg, color.bg);
	} else {
		csr.tile.Add(0, color.fg, color.bg);
		csr.tile.Add(0, color.bg, color.fg);
	}
	buf->SetTile(csr.tile, LAYER_1, csr.x + 1, csr.y + 1, false);
}
void t_editor_screen::print(string text) {
	for (auto& ch : text) {
		put_char(ch);
	}
}
void t_editor_screen::println(string text) {
	print(text + "\n");
}
void t_editor_screen::print_keep_cursor(string text) {
	int x = csr.x + 1;
	for (auto& ch : text) {
		buf->SetTile(TTileSeq(ch, color.fg, color.bg), LAYER_0, x, csr.y + 1, false);
		x++;
	}
}
void t_editor_screen::put_char(ixc ch) {
	if (ch != '\n') {
		buf->SetTile(TTileSeq(ch, color.fg, color.bg), LAYER_0, csr.x + 1, csr.y + 1, false);
		move_cursor(1, 0);
	} else {
		set_cursor(0, csr.y + 1);
	}
}
void t_editor_screen::set_tile(TTileSeq tile, int x, int y) {
	buf->SetTile(tile, LAYER_0, x + 1, y + 1, false);
}
void t_editor_screen::new_line() {
	set_cursor(0, csr.y + 1);
}
void t_editor_screen::scroll_up() {
}
void t_editor_screen::scroll_right() {
}
void t_editor_screen::scroll_left() {
}
