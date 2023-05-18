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
	void set_ch(int frame, int ch);
	void set_fgc(int frame, int fgc);
	void set_bgc(int frame, int bgc);
	bool parse(string str);
	string to_str();
};
struct t_tileset {
	vector<binary> tiles;
	t_tileset();
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
	t_tilebuf();
	t_tilebuf(int layer_count, int width, int height);
	void init(int layer_count, int width, int height);
	t_tilebuf_layer& layer(int index);
	void clear_all_layers();
private:
	vector<t_tilebuf_layer> layers;
	int width = 0;
	int height = 0;
};
struct t_tilebuf_collection {
	unordered_map<string, t_tilebuf> tilebufs;
	void new_tilebuf(string id, int layer_count, int width, int height);
	t_tilebuf& get(string id);
	bool has(string id);
	void select(string id);
	t_tilebuf* selected();
private:
	t_tilebuf* selected_buf = nullptr;
};
struct t_tilebuf_cursor {
	int layer = 0;
	int x = 0;
	int y = 0;
};

extern t_tileset tileset;
extern t_tilebuf_collection tilebufs;
extern t_tileseq working_tile;
extern t_tilebuf_cursor tilebuf_csr;
