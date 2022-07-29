#include "t_panel.h"
#include "chars.h"
#include "t_layer.h"

t_panel::t_panel(TTileBuffer* buf, int fgc, int bgc) : t_panel(buf, 0, 0, 0, 0, fgc, bgc) {
}
t_panel::t_panel(TTileBuffer* buf, int x, int y, int w, int h, int fgc, int bgc) {
	this->buf = buf;
	this->fgc = fgc;
	this->bgc = bgc;
	set_frame(x, y, w, h);
	title = "";
	bottom_text = "";
	title_x = 0;
	bottom_text_x = 0;
}
void t_panel::set_frame(int x, int y, int w, int h) {
	frame_x = x;
	frame_y = y;
	frame_w = w + 1;
	frame_h = h + 1;
}
void t_panel::draw_frame() {
	const int x = frame_x;
	const int y = frame_y;
	const int w = frame_w;
	const int h = frame_h;
	const int layer = t_layer::panel;
	const int ch_back = chars::empty;
	const int ch_tl = chars::pnl_corner_tl;
	const int ch_tr = chars::pnl_corner_tr;
	const int ch_bl = chars::pnl_corner_bl;
	const int ch_br = chars::pnl_corner_br;
	const int ch_hbar = chars::pnl_edge_h;
	const int ch_vbar = chars::pnl_edge_v;

	TTileSeq tile(0, fgc, bgc);

	// Corners
	tile.SetChar(0, ch_tl);
	buf->SetTile(tile, layer, x, y, false);
	tile.SetChar(0, ch_tr);
	buf->SetTile(tile, layer, x + w, y, false);
	tile.SetChar(0, ch_bl);
	buf->SetTile(tile, layer, x, y + h, false);
	tile.SetChar(0, ch_br);
	buf->SetTile(tile, layer, x + w, y + h, false);
	// Edges
	for (int edge_x = x + 1; edge_x < x + w; edge_x++) {
		tile.SetChar(0, ch_hbar);
		buf->SetTile(tile, layer, edge_x, y, false);
		buf->SetTile(tile, layer, edge_x, y + h, false);
	}
	for (int edge_y = y + 1; edge_y < y + h; edge_y++) {
		tile.SetChar(0, ch_vbar);
		buf->SetTile(tile, layer, x, edge_y, false);
		buf->SetTile(tile, layer, x + w, edge_y, false);
	}
	// Background
	for (int bg_y = y + 1; bg_y < y + h; bg_y++) {
		for (int bg_x = x + 1; bg_x < x + w; bg_x++) {
			tile.SetChar(0, ch_back);
			buf->SetTile(tile, layer, bg_x, bg_y, false);
		}
	}
	// Top text
	if (!title.empty()) {
		string visible_text;
		if (title.length() >= frame_w) {
			visible_text = String::Substring(title, 0, frame_w - 1);
		} else {
			visible_text = title;
		}
		buf->Print(visible_text, layer, frame_x + title_x + 1, frame_y, fgc, bgc, false);
	}
	// Bottom bottom
	if (!bottom_text.empty()) {
		string visible_text;
		if (bottom_text.length() >= frame_w) {
			visible_text = String::GetFirstChars(bottom_text, frame_w - 1);
		} else {
			visible_text = bottom_text;
		}
		buf->Print(visible_text, layer, frame_x + bottom_text_x + 1, frame_y + h, fgc, bgc, false);
	}
}
void t_panel::erase_frame() {
	buf->ClearLayerRect(t_layer::panel, frame_x, frame_y, frame_w, frame_h);
}
void t_panel::center_title() {
	if (!title.empty()) {
		title_x = ((frame_w / 2) - (title.length() / 2)) - 1;
		if (title_x < 0) title_x = 0;
	}
}
void t_panel::center_bottom_text() {
	if (!bottom_text.empty()) {
		bottom_text_x = ((frame_w / 2) - (bottom_text.length() / 2)) - 1;
		if (bottom_text_x < 0) bottom_text_x = 0;
	}
}
void t_panel::maximize(int margin) {
	frame_x = margin;
	frame_y = margin;
	frame_w = (buf->Cols - 1 - margin) - (margin);
	frame_h = (buf->Rows - 1 - margin) - (margin);
}
void t_panel::put_tile(TTileSeq tile, int x, int y, bool transparent) {
	buf->SetTile(tile, t_layer::panel, frame_x + x + 1, frame_y + y + 1, transparent);
}
void t_panel::erase_tile(int x, int y) {
	buf->EraseTile(t_layer::panel, frame_x + x + 1, frame_y + y + 1);
}
void t_panel::print(string text, int x, int y) {
	print(text, x, y, fgc);
}
void t_panel::print(string text, int x, int y, int text_fgc) {
	if (y < 0 || y >= frame_h - 1 || x >= frame_w - 1) {
		return;
	}
	const int px = x;
	for (auto& ch : text) {
		if (ch == '\n') {
			x = px;
			y++;
			if (y >= frame_h - 1) {
				break;
			}
		} else {
			put_tile(TTileSeq(ch, text_fgc, bgc), x, y, false);
			x++;
			if (x >= frame_w - 1) {
				break;
			}
		}
	}
}
