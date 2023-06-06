#pragma once
#include "../Common/common.h"
#include "ptm_graphics_base.h"

struct t_sprite;

struct t_tile {
	int ch = 0;
	int fgc = 0;
	int bgc = 0;
	bool transparent = false;
	t_tile();
	t_tile(int ch, int fgc, int bgc);
	t_tile(int ch, int fgc);
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
	void clear();
	void set_equal(t_tiledata& other);
private:
	unordered_map<string, string> data;
};
struct t_tileseq {
	vector<t_tile> frames;
	t_tiledata data;
	t_tileseq();
	t_tileseq(int ch, int fgc, int bgc);
	t_tileseq(int ch, int fgc);
	void clear();
	void set_equal(t_tileseq& other);
	void add(t_tile& frame);
	void add(int ch, int fgc, int bgc);
	void add(int ch, int fgc);
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
	void reset();
	binary blank_tile();
	void add_blank(int count = 1);
	void add(binary tile);
	void set(int index, binary tile);
	binary& get(int index);
	void set_size(int size);
};
struct t_search_pos {
	int x = PTM_INVALID_NUMBER;
	int y = PTM_INVALID_NUMBER;
	bool found = false;
	t_search_pos() : x(0), y(0), found(false) {}
	t_search_pos(int px, int py) : x(px), y(py), found(false) {}
	t_search_pos(int px, int py, bool is_found) : x(px), y(py), found(is_found) {}
	static t_search_pos not_found() { return t_search_pos(PTM_INVALID_NUMBER, PTM_INVALID_NUMBER, false); }
};
struct t_tilebuf_layer {
	t_tilebuf_layer();
	t_tilebuf_layer(int width, int height);
	void init(int width, int height);
	int get_width();
	int get_height();
	void put(int x, int y, t_tileseq& tileseq);
	void put(int x, int y, int ch, int fgc, int bgc);
	void put(int x, int y, int ch, int fgc);
	void add(int x, int y, t_tile& tile);
	void add(int x, int y, int ch, int fgc, int bgc);
	void add(int x, int y, int ch, int fgc);
	void fill(t_tileseq& tileseq);
	void fill_rect(t_tileseq& tileseq, int x1, int y1, int x2, int y2);
	void clear_rect(int x1, int y1, int x2, int y2);
	t_tileseq& get(int x, int y);
	t_tileseq get_copy(int x, int y);
	void del(int x, int y);
	bool empty(int x, int y);
	void clear();
	void move_tile(int x, int y, int dx, int dy);
	void move_block(int x1, int y1, int x2, int y2, int dx, int dy);
	t_search_pos find_with_data(t_search_pos begin_from, string data, string value);
	t_search_pos find_with_data(t_search_pos begin_from, string data, int value);
	t_search_pos find_with_data(t_search_pos begin_from, string data);
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
	void clear_layer(int layer);
	void clear_all_layers();
	void show();
	void hide();
	void toggle_visible();
	bool visible();
	vector<t_tilebuf_layer>& get_layers();
	int get_bgcol();
	void set_bgcol(int palette_ix);
	int get_width();
	int get_height();
	void add_sprite(t_sprite* sprite);
	vector<t_sprite*>& get_sprites();
private:
	vector<t_tilebuf_layer> layers;
	int width = 0;
	int height = 0;
	t_clip viewport;
	int bgcol_palette_ix = 0;
	bool is_visible = false;
	vector<t_sprite*> sprites;
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
	void clear_all_buffers();
private:
	t_tilebuf* selected_buf = nullptr;
	string selected_buf_id;
};
struct t_tilebuf_cursor {
	int layer = 0;
	int x = 0;
	int y = 0;
	void set(int layer, int x, int y) {
		this->layer = layer;
		this->x = x;
		this->y = y;
	}
	void set(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
struct t_tile_animation {
	int frame = 0;
	int ctr_next_frame = 0;
	int ctr_next_frame_max = 20;
	int enabled = true;
};

extern t_tileset tileset;
extern t_tilebuf_collection tilebufs;
extern t_tileseq working_tile;
extern t_tile_animation tile_animation;
extern t_tilebuf_cursor tilebuf_csr;

void ptm_reset_tilesystem();
void ptm_create_default_tilebuffer(int layers);
void ptm_draw_visible_buffers();
void ptm_draw_buffer(t_tilebuf* buf);
void ptm_update_tile_animation();
void ptm_set_tile_animation_speed(int speed);
t_tilebuf_layer& ptm_get_selected_tilebuf_layer();
void ptm_print_tile_string(string str, bool add_frames);
void ptm_print_tile_string(string str, int fgc, int bgc, bool add_frames);
void ptm_print_formatted_tile_string(string fmt);
void ptm_print_tile_char(int ch);
void ptm_store_tile(string id, t_tileseq& tile);
t_tileseq ptm_load_tile(string id);
bool ptm_has_stored_tile(string id);
string ptm_text_input(int maxlen);
bool ptm_text_input_ok();
void ptm_copy_tile_block(t_tilebuf_layer& buf, int x1, int y1, int x2, int y2);
void ptm_cut_tile_block(t_tilebuf_layer& buf, int x1, int y1, int x2, int y2);
void ptm_paste_tile_block(t_tilebuf_layer& buf, int x, int y);
