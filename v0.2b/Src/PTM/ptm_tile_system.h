#pragma once
#include "../Common/common.h"

struct t_tile {
	int ch = 0;
	int fgc = 0;
	int bgc = 0;
	t_tile();
	t_tile(int ch, int fgc, int bgc);
	void set_equal(t_tile& other);
};
struct t_tileseq {
	vector<t_tile> frames;
	t_tileseq();
	t_tileseq(int ch, int fgc, int bgc);
	void clear();
	void set_equal(t_tileseq& other);
	void add(t_tile& frame);
	void add(int ch, int fgc, int bgc);
	bool empty();
	int length();
};
struct t_tileset {
	vector<binary> tiles;
	binary blank_tile();
	void add_blank(int count = 1);
	void add(binary tile);
	void set(int index, binary tile);
	binary& get(int index);
};
struct t_tilebuf_layer {
	t_tilebuf_layer();
	t_tilebuf_layer(int width, int height);
	void init(int width, int height);
	void put(int x, int y, t_tileseq& tileseq);
	void put(int x, int y, int ch, int fgc, int bgc);
	void add(int x, int y, t_tile& tile);
	void add(int x, int y, int ch, int fgc, int bgc);
	t_tileseq& get(int x, int y);
	t_tileseq get_copy(int x, int y);
	void del(int x, int y);
	bool empty(int x, int y);
	void clear();
private:
	vector<t_tileseq> tiles;
	int width = 0;
	int height = 0;
};
struct t_tilebuf {
	void init(int layer_count, int width, int height);
	t_tilebuf_layer& layer(int index);
	void clear_all_layers();
private:
	vector<t_tilebuf_layer> layers;
	int width = 0;
	int height = 0;
};

extern t_tileset tileset;
