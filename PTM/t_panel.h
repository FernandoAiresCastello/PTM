#pragma once
#include "common.h"

struct t_panel {
	int frame_x;
	int frame_y;
	int frame_w;
	int frame_h;
	int fgc;
	int bgc;
	string title;
	string bottom_text;
	int title_x;
	int bottom_text_x;
	t_panel(TTileBuffer* buf, int x, int y, int w, int h, int fgc, int bgc);
	void draw_frame();
	void center_title();
	void center_bottom_text();
	void put_tile(TTileSeq tile, int x, int y, bool transparent);
	void erase_tile(int x, int y);
	void print(string text, int x, int y);
private:
	TTileBuffer* buf;
};
