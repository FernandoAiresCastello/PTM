#include "ptm_tile_system.h"
#include "ptm_text_font.h"
#include "ptm_color_palette.h"
#include "ptm_core.h"
#include "ptm_keyboard.h"
#include "ptm_sprites.h"

#define DEFAULT_TILEBUF_ID "default"

t_tileset tileset;
t_tilebuf_collection tilebufs;
t_tileseq working_tile;
t_tile_animation tile_animation;
t_tilebuf_cursor tilebuf_csr;
unordered_map<string, t_tileseq> tilestore;
bool text_input_cancelled = false;

struct {
	int width = 0;
	int height = 0;
	vector<t_tileseq> tiles;
} clipboard;

t_tile::t_tile()
{
	this->ch = 0;
	this->fgc = 0;
	this->bgc = 0;
	this->transparent = false;
}
t_tile::t_tile(int ch, int fgc, int bgc)
{
	this->ch = ch;
	this->fgc = fgc;
	this->bgc = bgc;
	this->transparent = false;
}
t_tile::t_tile(int ch, int fgc)
{
	this->ch = ch;
	this->fgc = fgc;
	this->bgc = bgc;
	this->transparent = true;
}
void t_tile::set_equal(t_tile& other)
{
	ch = other.ch;
	fgc = other.fgc;
	bgc = other.bgc;
	transparent = other.transparent;
}
void t_tiledata::set(string name, string value)
{
	data[name] = value;
}
void t_tiledata::set(string name, int value)
{
	data[name] = String::ToString(value);
}
string t_tiledata::get_s(string name)
{
	return data[name];
}
int t_tiledata::get_i(string name)
{
	return String::ToInt(data[name]);
}
bool t_tiledata::has(string name)
{
	return data.find(name) != data.end();
}
bool t_tiledata::has(string name, string value)
{
	return has(name) && get_s(name) == value;
}
bool t_tiledata::has(string name, int value)
{
	return has(name) && get_i(name) == value;
}
void t_tiledata::clear()
{
	data.clear();
}
void t_tiledata::set_equal(t_tiledata& other)
{
	data.clear();
	for (auto& item : other.data) {
		set(item.first, item.second);
	}
}
t_tileseq::t_tileseq()
{
}
t_tileseq::t_tileseq(int ch, int fgc, int bgc)
{
	frames.push_back(t_tile(ch, fgc, bgc));
}
t_tileseq::t_tileseq(int ch, int fgc)
{
	frames.push_back(t_tile(ch, fgc));
}
void t_tileseq::clear()
{
	frames.clear();
	data.clear();
}
void t_tileseq::set_equal(t_tileseq& other)
{
	clear();
	for (int i = 0; i < other.frames.size(); i++) {
		frames.push_back(other.frames[i]);
	}
	data.set_equal(other.data);
}
void t_tileseq::add(t_tile& frame)
{
	frames.push_back(frame);
}
void t_tileseq::add(int ch, int fgc, int bgc)
{
	frames.push_back(t_tile(ch, fgc, bgc));
}
void t_tileseq::add(int ch, int fgc)
{
	frames.push_back(t_tile(ch, fgc));
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
		if (String::ToUpper(data[2]) == "T") {
			add(ch, fgc);
		}
		else {
			int bgc = String::ToInt(data[2]);
			add(ch, fgc, bgc);
		}
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
	reset();
}
void t_tileset::reset()
{
	new_tileset(256, true);
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
void t_tileset::new_tileset(int size, bool init_default_font)
{
	tiles.clear();
	add_blank(size);
	if (init_default_font) {
		ptm_init_text_font();
	}
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
int t_tilebuf_layer::get_width()
{
	return width;
}
int t_tilebuf_layer::get_height()
{
	return height;
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
void t_tilebuf_layer::put(int x, int y, int ch, int fgc)
{
	t_tileseq tile(ch, fgc);
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
void t_tilebuf_layer::add(int x, int y, int ch, int fgc)
{
	if (x >= 0 && y >= 0 && x < width && y < width) {
		get(x, y).add(ch, fgc);
	}
}
void t_tilebuf_layer::fill(t_tileseq& tileseq)
{
	for (int i = 0; i < width * height; i++) {
		tiles[i].set_equal(tileseq);
	}
}
void t_tilebuf_layer::fill_rect(t_tileseq& tileseq, int x1, int y1, int x2, int y2)
{
	for (int py = y1; py <= y2; py++) {
		for (int px = x1; px <= x2; px++) {
			if (px >= 0 && py >= 0 && px < width && py < height) {
				get(px, py).set_equal(tileseq);
			}
		}
	}
}
void t_tilebuf_layer::clear_rect(int x1, int y1, int x2, int y2)
{
	for (int py = y1; py <= y2; py++) {
		for (int px = x1; px <= x2; px++) {
			if (px >= 0 && py >= 0 && px < width && py < height) {
				del(px, py);
			}
		}
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
void t_tilebuf_layer::move_tile(int x, int y, int dx, int dy)
{
	t_tileseq tile = get_copy(x, y);
	put(x + dx, y + dy, tile);
	del(x, y);
}
void t_tilebuf_layer::move_block(int x1, int y1, int x2, int y2, int dx, int dy)
{
	vector<t_tileseq> tiles;
	for (int cy = y1; cy <= y2; cy++) {
		for (int cx = x1; cx <= x2; cx++) {
			if (cx >= 0 && cy >= 0 && cx < width && cy < height) {
				tiles.push_back(get_copy(cx, cy));
				del(cx, cy);
			}
			else {
				tiles.push_back(t_tileseq());
			}
		}
	}
	const int new_x1 = x1 + dx;
	const int new_y1 = y1 + dy;
	const int new_x2 = x2 + dx;
	const int new_y2 = y2 + dy;
	int i = 0;
	for (int cy = new_y1; cy <= new_y2; cy++) {
		for (int cx = new_x1; cx <= new_x2; cx++) {
			put(cx, cy, tiles[i++]);
		}
	}
}
t_search_pos t_tilebuf_layer::find_with_data(t_search_pos begin_from, string data, string value)
{
	for (int y = begin_from.y; y < height; y++) {
		for (int x = begin_from.x; x < width; x++) {
			if (get(x, y).data.has(data, value)) {
				return t_search_pos(x, y, true);
			}
		}
	}
	return t_search_pos::not_found();
}
t_search_pos t_tilebuf_layer::find_with_data(t_search_pos begin_from, string data, int value)
{
	return find_with_data(begin_from, data, String::ToString(value));
}
t_search_pos t_tilebuf_layer::find_with_data(t_search_pos begin_from, string data)
{
	for (int y = begin_from.y; y < height; y++) {
		for (int x = begin_from.x; x < width; x++) {
			if (get(x, y).data.has(data)) {
				return t_search_pos(x, y, true);
			}
		}
	}
	return t_search_pos::not_found();
}
t_tilebuf::t_tilebuf()
{
}
t_tilebuf::t_tilebuf(string id, int layer_count, int width, int height, int order)
{
	init(id, layer_count, width, height, order);
}
void t_tilebuf::init(string id, int layer_count, int width, int height, int order)
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->order = order;

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
void t_tilebuf::clear_layer(int layer)
{
	layers[layer].clear();
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
void t_tilebuf::toggle_visible()
{
	if (is_visible)
		hide();
	else
		show();
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
	bg_enabled = true;
}
int t_tilebuf::get_width()
{
	return width;
}
int t_tilebuf::get_height()
{
	return height;
}
void t_tilebuf::add_sprite(t_sprite* sprite)
{
	if (std::find(sprites.begin(), sprites.end(), sprite) == sprites.end()) {
		sprites.push_back(sprite);
		sprite->add_to_buffer(this);
	}
}
vector<t_sprite*>& t_tilebuf::get_sprites()
{
	return sprites;
}
void t_tilebuf_collection::new_tilebuf(string id, int layer_count, int width, int height, int order)
{
	t_tilebuf tilebuf(id, layer_count, width, height, order);
	tilebufs.push_back(tilebuf);
}
t_tilebuf* t_tilebuf_collection::get(string id)
{
	for (auto& tilebuf : tilebufs) {
		if (tilebuf.id == id)
			return &tilebuf;
	}
	return nullptr;
}
t_tilebuf* t_tilebuf_collection::get_by_order(int order)
{
	for (auto& tilebuf : tilebufs) {
		if (tilebuf.order == order)
			return &tilebuf;
	}
	return nullptr;
}
bool t_tilebuf_collection::has(string id)
{
	for (auto& tilebuf : tilebufs) {
		if (tilebuf.id == id)
			return true;
	}
	return false;
}
void t_tilebuf_collection::select(string id)
{
	selected_buf = get(id);
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
void t_tilebuf_collection::clear_all_buffers()
{
	for (auto& tilebuf : tilebufs) {
		tilebuf.clear_all_layers();
	}
}
void ptm_reset_tilesystem()
{
	tileset.reset();
	tilebufs.tilebufs.clear();
	working_tile.clear();
	tilebuf_csr.set(0, 0, 0);
}
void ptm_create_default_tilebuffer(int layers)
{
	tilebufs.new_tilebuf(DEFAULT_TILEBUF_ID, layers, scr.cols, scr.rows, 0);
	tilebufs.select(DEFAULT_TILEBUF_ID);
	tilebufs.get(DEFAULT_TILEBUF_ID)->view(0, 0, scr.buf_w - 1, scr.buf_h - 1);
	tilebufs.get(DEFAULT_TILEBUF_ID)->set_bgcol(0);
	tilebufs.get(DEFAULT_TILEBUF_ID)->show();
}
void ptm_draw_visible_buffers()
{
	for (int i = 0; i < tilebufs.tilebufs.size(); i++) {
		ptm_draw_buffer(tilebufs.get_by_order(i));
	}
}
void ptm_draw_buffer(t_tilebuf* buf)
{
	if (!buf->visible())
		return;

	ptm_clip(buf->get_viewport());
	if (buf->bg_enabled) {
		ptm_fill_clip(palette.get(buf->get_bgcol()));
	}

	for (auto& layer : buf->get_layers()) {
		for (int y = 0; y < buf->get_height(); y++) {
			for (int x = 0; x < buf->get_width(); x++) {
				t_tileseq& tile = layer.get(x, y);
				if (tile.empty()) {
					continue;
				}
				t_tile& frame = tile.frames[tile_animation.frame % tile.length()];
				binary& bin = tileset.get(frame.ch);
				rgb fgc = palette.get(frame.fgc);
				rgb bgc = palette.get(frame.bgc);
				ptm_draw_tile_bin(bin, x * PTM_TILE_SIZE, y * PTM_TILE_SIZE, fgc, bgc, frame.transparent);
			}
		}
	}
	for (auto* sprite : buf->get_sprites()) {
		sprite->draw();
	}
}
void ptm_update_tile_animation()
{
	if (!tile_animation.enabled)
		return;

	tile_animation.ctr_next_frame++;
	if (tile_animation.ctr_next_frame >= tile_animation.ctr_next_frame_max) {
		tile_animation.ctr_next_frame = 0;
		tile_animation.frame++;
	}
}
void ptm_set_tile_animation_speed(int speed)
{
	if (speed <= 0) {
		tile_animation.enabled = false;
		return;
	}
	if (speed > 100) {
		speed = 100;
	}
	tile_animation.enabled = true;
	tile_animation.ctr_next_frame = 0;
	tile_animation.ctr_next_frame_max = 100 - speed;
}
t_tilebuf_layer& ptm_get_selected_tilebuf_layer()
{
	return tilebufs.selected()->layer(tilebuf_csr.layer);
}
void ptm_print_tile_string(string str, bool add_frames)
{
	ptm_print_tile_string(str, scr.text_style.fgc, scr.text_style.bgc, add_frames);
}
void ptm_print_tile_string(string str, int fgc, int bgc, bool add_frames)
{
	t_tilebuf_layer& layer = ptm_get_selected_tilebuf_layer();
	int x = tilebuf_csr.x;
	int y = tilebuf_csr.y;
	bool transparent = scr.text_style.transparent;
	bool escape = false;

	for (auto& ch : str) {
		if (ch == '\\') {
			escape = true;
			continue;
		}
		if (escape && ch == 'n') {
			y++;
			x = tilebuf_csr.x;
			continue;
		}
		escape = false;
		if (add_frames) {
			if (transparent)
				layer.add(x, y, ch, fgc);
			else
				layer.add(x, y, ch, fgc, bgc);
		}
		else {
			if (transparent)
				layer.put(x, y, ch, fgc);
			else
				layer.put(x, y, ch, fgc, bgc);
		}
		x++;
	}

	tilebuf_csr.set(x, y);
}
void ptm_print_tile_char(int ch)
{
	if (scr.text_style.transparent) {
		ptm_get_selected_tilebuf_layer()
			.put(tilebuf_csr.x, tilebuf_csr.y, ch, scr.text_style.fgc);
	}
	else {
		ptm_get_selected_tilebuf_layer()
			.put(tilebuf_csr.x, tilebuf_csr.y, ch, scr.text_style.fgc, scr.text_style.bgc);
	}
	tilebuf_csr.x++;
}
void ptm_store_tile(string id, t_tileseq& tile)
{
	tilestore[id] = tile;
}
t_tileseq ptm_load_tile(string id)
{
	return tilestore[id];
}
bool ptm_has_stored_tile(string id)
{
	return tilestore.find(id) != tilestore.end();
}
string ptm_text_input(int maxlen)
{
	text_input_cancelled = false;
	
	string text = "";
	const string blanks = String::Repeat(' ', maxlen + 1);
	const int initial_x = tilebuf_csr.x;
	const int initial_y = tilebuf_csr.y;

	bool finished = false;

	while (!finished) {

		tilebuf_csr.x = initial_x;
		ptm_print_tile_string(blanks, false);
		tilebuf_csr.x = initial_x;
		ptm_print_tile_string(text + "_", false);

		ptm_refresh_window();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);

		if (e.type == SDL_QUIT) {
			ptm_exit();
			return "";
		}
		else if (e.type == SDL_KEYDOWN) {
			SDL_Keycode key = e.key.keysym.sym;

			// ALT+ENTER = Fullscreen
			if (key == SDLK_RETURN && ptm_kb_alt()) {
				ptm_toggle_fullscreen();
			}
			// ENTER = Confirm
			else if (key == SDLK_RETURN && !ptm_kb_alt()) {
				finished = true;
			}
			// ESC = Cancel
			else if (key == SDLK_ESCAPE) {
				text_input_cancelled = true;
				finished = true;
			}
			// BACKSPACE = Erase last char
			else if (key == SDLK_BACKSPACE) {
				if (!text.empty()) {
					text.pop_back();
				}
			}
			// HOME = Clear
			else if (key == SDLK_HOME) {
				text = "";
			}
			// Any other typable character
			else if (text.length() < maxlen) {
				char ch = ptm_keycode_to_char(key);
				if (ch) {
					text += ch;
				}
			}
		}
	}

	last_key = 0; // Clear last key, so as not to interfere with the kb_inkey function
	t_tilebuf_layer& buf = ptm_get_selected_tilebuf_layer();
	buf.del(tilebuf_csr.x - 1, tilebuf_csr.y); // Delete cursor character
	tilebuf_csr.x = initial_x;

	return text;
}
bool ptm_text_input_ok()
{
	return !text_input_cancelled;
}
void ptm_print_formatted_tile_string(string fmt)
{
	t_tilebuf_layer& layer = ptm_get_selected_tilebuf_layer();
	int initial_x = tilebuf_csr.x;
	int initial_y = tilebuf_csr.y;
	int fgc = scr.text_style.fgc;
	int bgc = scr.text_style.bgc;

	bool escape = false;
	string escape_seq = "";
	for (int i = 0; i < fmt.length(); i++) {
		int ch = fmt[i];
		if (ch == '\\') {
			i++;
			if (i < fmt.length()) {
				if (fmt[i] == 'n') {
					tilebuf_csr.set(initial_x, tilebuf_csr.y + 1);
				}
			}
		}
		else if (ch == '{') {
			escape = true;
			continue;
		}
		else if (ch == '}') {
			escape = false;
			const string upper_escape_seq = String::ToUpper(escape_seq);
			if (String::StartsWith(upper_escape_seq, 'C')) {
				ch = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
				auto tile = t_tileseq(ch, fgc, bgc);
				layer.put(tilebuf_csr.x, tilebuf_csr.y, tile);
				tilebuf_csr.x++;
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, 'F')) {
				fgc = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, "/F")) {
				fgc = scr.text_style.fgc;
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, 'B')) {
				bgc = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, "/B")) {
				bgc = scr.text_style.bgc;
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(escape_seq, '%')) {
				string var = String::Skip(escape_seq, 1);
				if (String::Contains(var, '[') || String::Contains(var, ']')) {
					auto begin = String::IndexOf(var, '[');
					auto end = String::IndexOf(var, ']');
					if (begin != string::npos && end != string::npos && begin < end) {
						string arr_id = String::Substring(var, 0, begin);
						if (intp->arrays.find(arr_id) != intp->arrays.end()) {
							string ixs = String::Substring(var, begin + 1, end);
							int ix = -1;
							if (String::IsNumber(ixs)) {
								ix = String::ToInt(ixs);
							}
							else {
								if (intp->vars.find(ixs) != intp->vars.end()) {
									ix = String::ToInt(intp->vars[ixs].value);
								}
								else {
									intp->abort("Variable not found: " + ixs);
								}
							}
							if (ix >= 0 && ix < intp->arrays[arr_id].size()) {
								string str = intp->arrays[arr_id].at(ix);
								ptm_print_tile_string(str, fgc, bgc, false);
							}
							else {
								intp->abort(String::Format("Array index out of bounds: %s[%i]", arr_id.c_str(), ix));
							}
						}
						else {
							intp->abort("Array not found: " + arr_id);
						}
					}
				}
				else {
					if (intp->vars.find(var) != intp->vars.end()) {
						ptm_print_tile_string(intp->vars[var].value, fgc, bgc, false);
					}
					else {
						intp->abort("Variable not found: " + var);
					}
				}
				escape_seq = "";
				continue;
			}
			else {
				intp->abort("Invalid escape sequence: " + escape_seq);
			}
		}
		else if (escape) {
			escape_seq += ch;
			continue;
		}
		else {
			auto tile = scr.text_style.transparent ? t_tileseq(ch, fgc) : t_tileseq(ch, fgc, bgc);
			layer.put(tilebuf_csr.x, tilebuf_csr.y, tile);
			tilebuf_csr.x++;
			escape_seq = "";
		}
	}
}
void ptm_copy_tile_block(t_tilebuf_layer& buf, int x1, int y1, int x2, int y2)
{
	clipboard.tiles.clear();
	clipboard.width = x2 - x1;
	clipboard.height = y2 - y1;

	for (int cy = y1; cy <= y2; cy++) {
		for (int cx = x1; cx <= x2; cx++) {
			if (cx >= 0 && cy >= 0 && cx < buf.get_width() && cy < buf.get_height()) {
				clipboard.tiles.push_back(buf.get_copy(cx, cy));
			}
			else {
				clipboard.tiles.push_back(t_tileseq());
			}
		}
	}
}
void ptm_cut_tile_block(t_tilebuf_layer& buf, int x1, int y1, int x2, int y2)
{
	ptm_copy_tile_block(buf, x1, y1, x2, y2);
	buf.clear_rect(x1, y1, x2, y2);
}
void ptm_paste_tile_block(t_tilebuf_layer& buf, int x, int y)
{
	int i = 0;
	for (int py = y; py <= y + clipboard.height; py++) {
		for (int px = x; px <= x + clipboard.width; px++) {
			t_tileseq& tile = clipboard.tiles[i++];
			buf.put(px, py, tile);
		}
	}
}
