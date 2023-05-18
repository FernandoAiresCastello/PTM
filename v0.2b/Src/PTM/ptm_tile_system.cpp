#include "ptm_tile_system.h"
#include "ptm_text_font.h"
#include "ptm_color_palette.h"

#define DEFAULT_TILEBUF_ID "default"

t_tileset tileset;
t_tilebuf_collection tilebufs;
t_tileseq working_tile;
t_tilebuf_cursor tilebuf_csr;

struct {
	int frame = 0;
	int ctr_next_frame = 0;
	int ctr_next_frame_max = 20;
	int enabled = true;
} animation;

t_tile::t_tile()
{
	this->ch = 0;
	this->fgc = 0;
	this->bgc = 0;
}
t_tile::t_tile(int ch, int fgc, int bgc)
{
	this->ch = ch;
	this->fgc = fgc;
	this->bgc = bgc;
}
void t_tile::set_equal(t_tile& other)
{
	ch = other.ch;
	fgc = other.fgc;
	bgc = other.bgc;
}
t_tileseq::t_tileseq()
{
}
t_tileseq::t_tileseq(int ch, int fgc, int bgc)
{
	frames.push_back(t_tile(ch, fgc, bgc));
}
void t_tileseq::clear()
{
	frames.clear();
}
void t_tileseq::set_equal(t_tileseq& other)
{
	clear();
	for (int i = 0; i < other.frames.size(); i++) {
		frames.push_back(other.frames[i]);
	}
}
void t_tileseq::add(t_tile& frame)
{
	frames.push_back(frame);
}
void t_tileseq::add(int ch, int fgc, int bgc)
{
	frames.push_back(t_tile(ch, fgc, bgc));
}
bool t_tileseq::empty()
{
	return frames.empty();
}
int t_tileseq::length()
{
	return frames.size();
}
void t_tileseq::set_ch(int frame, int ch)
{
	frames[frame].ch = ch;
}
void t_tileseq::set_fgc(int frame, int fgc)
{
	frames[frame].fgc = fgc;
}
void t_tileseq::set_bgc(int frame, int bgc)
{
	frames[frame].bgc = bgc;
}
bool t_tileseq::parse(string str)
{
	clear();
	auto tiles = String::Split(str, ';', true);
	for (auto& tile : tiles) {
		auto data = String::Split(tile, ',', true);
		if (data.size() != 3) {
			return false;
		}
		int ch = String::ToInt(data[0]);
		int fgc = String::ToInt(data[1]);
		int bgc = String::ToInt(data[2]);
		add(ch, fgc, bgc);
	}
	return true;
}
string t_tileseq::to_str()
{
	string str;
	for (auto& tile : frames) {
		str += String::Format("%i,%i,%i;", tile.ch, tile.fgc, tile.bgc);
	}
	return str;
}
t_tileset::t_tileset()
{
	add_blank(256);
	ptm_init_text_font();
}
binary t_tileset::blank_tile()
{
	return string(64, '0');
}
void t_tileset::add_blank(int count)
{
	for (int i = 0; i < count; i++) {
		tiles.push_back(blank_tile());
	}
}
void t_tileset::add(binary tile)
{
	tiles.push_back(tile);
}
void t_tileset::set(int index, binary tile)
{
	tiles[index] = tile;
}
binary& t_tileset::get(int index)
{
	return tiles[index];
}
t_tilebuf_layer::t_tilebuf_layer()
{
}
t_tilebuf_layer::t_tilebuf_layer(int width, int height)
{
	init(width, height);
}
void t_tilebuf_layer::init(int width, int height)
{
	this->width = width;
	this->height = height;

	tiles.clear();
	for (int i = 0; i < width * height; i++) {
		tiles.push_back(t_tileseq());
	}
}
void t_tilebuf_layer::put(int x, int y, t_tileseq& tileseq)
{
	if (x >= 0 && y >= 0 && x < width && y < width) {
		const int ix = y * width + x;
		tiles[ix] = tileseq;
	}
}
void t_tilebuf_layer::put(int x, int y, int ch, int fgc, int bgc)
{
	t_tileseq tile(ch, fgc, bgc);
	put(x, y, tile);
}
void t_tilebuf_layer::add(int x, int y, t_tile& tile)
{
	if (x >= 0 && y >= 0 && x < width && y < width) {
		get(x, y).add(tile);
	}
}
void t_tilebuf_layer::add(int x, int y, int ch, int fgc, int bgc)
{
	if (x >= 0 && y >= 0 && x < width && y < width) {
		get(x, y).add(ch, fgc, bgc);
	}
}
void t_tilebuf_layer::fill(t_tileseq& tileseq)
{
	for (int i = 0; i < width * height; i++) {
		tiles[i].set_equal(tileseq);
	}
}
t_tileseq& t_tilebuf_layer::get(int x, int y)
{
	const int ix = y * width + x;
	return tiles[ix];
}
t_tileseq t_tilebuf_layer::get_copy(int x, int y)
{
	return get(x, y);
}
void t_tilebuf_layer::del(int x, int y)
{
	if (x >= 0 && y >= 0 && x < width && y < width) {
		get(x, y).clear();
	}
}
bool t_tilebuf_layer::empty(int x, int y)
{
	return get(x, y).empty();
}
void t_tilebuf_layer::clear()
{
	for (auto& tileseq : tiles) {
		tileseq.clear();
	}
}
t_tilebuf::t_tilebuf()
{
}
t_tilebuf::t_tilebuf(int layer_count, int width, int height)
{
	init(layer_count, width, height);
}
void t_tilebuf::init(int layer_count, int width, int height)
{
	this->width = width;
	this->height = height;
	for (int i = 0; i < layer_count; i++) {
		layers.push_back(t_tilebuf_layer(width, height));
	}
}
void t_tilebuf::view(int x1, int y1, int x2, int y2)
{
	viewport.x1 = x1;
	viewport.y1 = y1;
	viewport.x2 = x2;
	viewport.y2 = y2;
}
void t_tilebuf::scroll_view(int dx, int dy)
{
	viewport.x_offset -= dx;
	viewport.y_offset -= dy;
}
t_clip& t_tilebuf::get_viewport()
{
	return viewport;
}
t_tilebuf_layer& t_tilebuf::layer(int index)
{
	return layers[index];
}
int t_tilebuf::get_layer_count()
{
	return layers.size();
}
void t_tilebuf::clear_all_layers()
{
	for (auto& layer : layers) {
		layer.clear();
	}
}
void t_tilebuf::show()
{
	is_visible = true;
}
void t_tilebuf::hide()
{
	is_visible = false;
}
bool t_tilebuf::visible()
{
	return is_visible;
}
vector<t_tilebuf_layer>& t_tilebuf::get_layers()
{
	return layers;
}
int t_tilebuf::get_bgcol()
{
	return bgcol_palette_ix;
}
void t_tilebuf::set_bgcol(int palette_ix)
{
	bgcol_palette_ix = palette_ix;
}
int t_tilebuf::get_width()
{
	return width;
}
int t_tilebuf::get_height()
{
	return height;
}
void t_tilebuf_collection::new_tilebuf(string id, int layer_count, int width, int height)
{
	t_tilebuf tilebuf(layer_count, width, height);
	tilebufs[id] = tilebuf;
}
t_tilebuf& t_tilebuf_collection::get(string id)
{
	return tilebufs[id];
}
bool t_tilebuf_collection::has(string id)
{
	return tilebufs.find(id) != tilebufs.end();
}
void t_tilebuf_collection::select(string id)
{
	selected_buf = &tilebufs[id];
	selected_buf_id = id;
}
t_tilebuf* t_tilebuf_collection::selected()
{
	return selected_buf;
}
string t_tilebuf_collection::selected_id()
{
	return selected_buf_id;
}
void ptm_create_default_tilebuffer(int layers)
{
	tilebufs.new_tilebuf(DEFAULT_TILEBUF_ID, layers, scr.cols, scr.rows);
	tilebufs.select(DEFAULT_TILEBUF_ID);
	tilebufs.get(DEFAULT_TILEBUF_ID).view(0, 0, scr.buf_w - 1, scr.buf_h - 1);
	tilebufs.get(DEFAULT_TILEBUF_ID).set_bgcol(0);
	tilebufs.get(DEFAULT_TILEBUF_ID).show();
}
void ptm_draw_visible_buffers()
{
	ptm_draw_buffer(tilebufs.get(DEFAULT_TILEBUF_ID));

	for (auto& entry : tilebufs.tilebufs) {
		if (entry.first != DEFAULT_TILEBUF_ID) {
			t_tilebuf& buf = entry.second;
			ptm_draw_buffer(buf);
		}
	}
}
void ptm_draw_buffer(t_tilebuf& buf)
{
	if (!buf.visible())
		return;

	ptm_clip(buf.get_viewport());
	ptm_fill_clip(palette.get(buf.get_bgcol()));

	for (auto& layer : buf.get_layers()) {
		for (int y = 0; y < buf.get_height(); y++) {
			for (int x = 0; x < buf.get_width(); x++) {
				t_tileseq& tile = layer.get(x, y);
				if (tile.empty()) {
					continue;
				}
				t_tile& frame = tile.frames[animation.frame % tile.length()];
				binary& bin = tileset.get(frame.ch);
				rgb fgc = palette.get(frame.fgc);
				rgb bgc = palette.get(frame.bgc);
				ptm_draw_tile_bin(bin, x * 8, y * 8, fgc, bgc, false);
			}
		}
	}
}
void ptm_update_tile_animation()
{
	if (!animation.enabled)
		return;

	animation.ctr_next_frame++;
	if (animation.ctr_next_frame >= animation.ctr_next_frame_max) {
		animation.ctr_next_frame = 0;
		animation.frame++;
	}
}
void ptm_set_tile_animation_speed(int speed)
{
	if (speed <= 0) {
		animation.enabled = false;
		return;
	}
	if (speed > 100) {
		speed = 100;
	}
	animation.enabled = true;
	animation.ctr_next_frame = 0;
	animation.ctr_next_frame_max = 100 - speed;
}
t_tilebuf_layer& ptm_get_selected_tilebuf_layer()
{
	return tilebufs.selected()->layer(tilebuf_csr.layer);
}
void ptm_print_tile_string(string str)
{
	t_tilebuf_layer& layer = ptm_get_selected_tilebuf_layer();
	int x = tilebuf_csr.x;
	int y = tilebuf_csr.y;

	for (auto& ch : str) {
		layer.put(x, y, ch, scr.text_style.fgc, scr.text_style.bgc);
		x++;
	}
}
