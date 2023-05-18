#include "ptm_tile_system.h"

t_tileset tileset;
t_tilebuf_collection tilebufs;
t_tileseq working_tile;
t_tilebuf_cursor tilebuf_csr;

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
	const int ix = y * width + x;
	tiles[ix] = tileseq;
}
void t_tilebuf_layer::put(int x, int y, int ch, int fgc, int bgc)
{
	t_tileseq tile(ch, fgc, bgc);
	put(x, y, tile);
}
void t_tilebuf_layer::add(int x, int y, t_tile& tile)
{
	get(x, y).add(tile);
}
void t_tilebuf_layer::add(int x, int y, int ch, int fgc, int bgc)
{
	get(x, y).add(ch, fgc, bgc);
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
	get(x, y).clear();
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
t_tilebuf_layer& t_tilebuf::layer(int index)
{
	return layers[index];
}
void t_tilebuf::clear_all_layers()
{
	for (auto& layer : layers) {
		layer.clear();
	}
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
}
t_tilebuf* t_tilebuf_collection::selected()
{
	return selected_buf;
}
