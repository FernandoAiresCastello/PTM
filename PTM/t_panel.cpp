#include "t_panel.h"

t_panel::t_panel(TTileBuffer* buf, int x, int y, int w, int h, int fgc, int bgc) {
	this->buf = buf;
	frame_x = x;
	frame_y = y;
	frame_w = w + 1;
	frame_h = h + 1;
	this->fgc = fgc;
	this->bgc = bgc;
}
void t_panel::draw_frame() {
	const int x = frame_x;
	const int y = frame_y;
	const int w = frame_w;
	const int h = frame_h;
	const int layer = 0;
	const int ch_back = 0x00;
	const int ch_tl = 0xda;
	const int ch_tr = 0xbf;
	const int ch_bl = 0xc0;
	const int ch_br = 0xd9;
	const int ch_hbar = 0xc4;
	const int ch_vbar = 0xb3;

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
}
void t_panel::put_tile(TTileSeq tile, int x, int y, bool transparent) {
	const int layer = 0;
	buf->SetTile(tile, layer, frame_x + x + 1, frame_y + y + 1, transparent);
}
void t_panel::erase_tile(int x, int y) {
	const int layer = 0;
	buf->EraseTile(layer, frame_x + x + 1, frame_y + y + 1);
}
void t_panel::print(string text, int x, int y) {
	const int layer = 0;
	for (auto& ch : text) {
		put_tile(TTileSeq(ch, fgc, bgc), x, y, false);
		x++;
		if (x >= frame_w - 1) {
			break;
		}
	}
}
