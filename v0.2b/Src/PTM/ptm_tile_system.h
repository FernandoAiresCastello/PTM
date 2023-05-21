#pragma once
#include "../Common/common.h"
#include "ptm_graphics_base.h"

struct t_tile {
	int ch = 0;
	int fgc = 0;
	int bgc = 0;
	t_tile();
	t_tile(int ch, int fgc, int bgc);
	void set_equal(t_tile& other);
};
struct t_tiledata {
	void set(string name, string value);
	void set(string name, int value);
	string get_s(string name);
	int get_i(string name);
	bool has(string name);
	bool has(string name, string value);
	bool has(string name, int value);
private:
	unordered_map<string, string> data;
};
struct t_tileseq {
	vector<t_tile> frames;
	bool transparent = false;
	t_tiledata data;
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
	void fill(t_tileseq& tileseq);
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
	string id;
	int order = 0;
	bool bg_enabled = true;
	t_tilebuf();
	t_tilebuf(string id, int layer_count, int width, int height, int order);
	void init(string id, int layer_count, int width, int height, int order);
	void view(int x1, int y1, int x2, int y2);
	void scroll_view(int dx, int dy);
	t_clip& get_viewport();
	t_tilebuf_layer& layer(int index);
	int get_layer_count();
	void clear_all_layers();
	void show();
	void hide();
	bool visible();
	vector<t_tilebuf_layer>& get_layers();
	int get_bgcol();
	void set_bgcol(int palette_ix);
	int get_width();
	int get_height();
private:
	vector<t_tilebuf_layer> layers;
	int width = 0;
	int height = 0;
	t_clip viewport;
	int bgcol_palette_ix = 0;
	bool is_visible = false;
};
struct t_tilebuf_collection {
	vector<t_tilebuf> tilebufs;
	void new_tilebuf(string id, int layer_count, int width, int height, int order);
	t_tilebuf* get(string id);
	t_tilebuf* get_by_order(int order);
	bool has(string id);
	void select(string id);
	t_tilebuf* selected();
	string selected_id();
private:
	t_tilebuf* selected_buf = nullptr;
	string selected_buf_id;
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

void ptm_create_default_tilebuffer(int layers);
void ptm_draw_visible_buffers();
void ptm_draw_buffer(t_tilebuf* buf);
void ptm_update_tile_animation();
void ptm_set_tile_animation_speed(int speed);
t_tilebuf_layer& ptm_get_selected_tilebuf_layer();
void ptm_print_tile_string(string str);
void ptm_print_tile_char(int ch);
void ptm_store_tile(string id, t_tileseq& tile);
t_tileseq ptm_load_tile(string id);
bool ptm_has_stored_tile(string id);
