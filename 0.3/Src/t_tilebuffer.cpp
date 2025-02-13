#include <memory>
#include "t_tilebuffer.h"
#include "t_window.h"
#include "t_charset.h"
#include "t_palette.h"
#include "predefined_charset_ix.h"
#include "t_filesystem.h"

#define tile_at(x, y)			tiles[y * cols + x]
#define if_inside_bounds(x, y)	if (x >= 0 && y >= 0 && x < cols && y < rows)
#define if_out_of_bounds(x, y)	if (x < 0 || y < 0 || x >= cols || y >= rows)

#define USR_WIDTH	41
#define USR_HEIGHT	23
#define LAYER_COUNT	1

t_tilebuffer::t_tilebuffer() : t_tilebuffer(t_window::cols, t_window::rows)
{
}

t_tilebuffer::t_tilebuffer(int cols, int rows) : 
	cols(cols), rows(rows), last_col(cols - 1), last_row(rows-1), length(cols * rows)
{
	for (int i = 0; i < length; i++)
		tiles.emplace_back();

	clear();

	cursor_sprite = std::make_shared<t_sprite>(
		t_tile(predef_char.cursor, 0, 0, t_tileflags()), t_pos(0, 0), true, true);

	cursor_sprite->enabled = true;
}

void t_tilebuffer::draw(t_window* wnd, t_charset* chr, t_palette* pal, const t_pos& scr_pos, const t_tilebuffer_region& region)
{
	int px = 0;
	int py = 0;

	for (int y = region.offset_y; y < region.offset_y + region.height; y++) {
		for (int x = region.offset_x; x < region.offset_x + region.width; x++) {

			t_tile& tile = tile_at(x, y);
			draw_tile_absolute_pos(tile, wnd, chr, pal, scr_pos.x + px, scr_pos.y + py, true);

			if (cursor_sprite->get_x() == x && cursor_sprite->get_y() == y)
				draw_tile_absolute_pos(cursor_sprite->get_tile(), wnd, chr, pal, scr_pos.x + px, scr_pos.y + py, true);

			px++;
		}
		py++;
		px = 0;
	}

	if (sprites_enabled) {
		for (auto& spr : sprites.get_all()) {
			if (spr.enabled)
				draw_tile_absolute_pos(spr.get_tile(), wnd, chr, pal, spr.get_x(), spr.get_y(), false);
		}
	}
}

void t_tilebuffer::draw_tile_absolute_pos(t_tile& tile, t_window* wnd, t_charset* chr, t_palette* pal, int x, int y, bool grid) const
{
	if (tile.flags.visible) {
		t_char& ch = tile.get_char_wraparound(wnd->get_animation_frame());
		wnd->draw_pixels(chr->get(ch.ix), x, y, pal->get(ch.fgc), pal->get(ch.bgc), grid, tile.flags.hide_bgc);
	}
}

void t_tilebuffer::set(const t_tile& tile, int x, int y)
{
	if_inside_bounds(x, y)
		tile_at(x, y) = tile;
}

void t_tilebuffer::set_text(const t_string& text, int x, int y, t_index fgc, t_index bgc, t_tileflags flags)
{
	for (auto& ch : text.s_str()) {
		if_out_of_bounds(x, y)
			break;
		
		tile_at(x, y) = t_tile(ch, fgc, bgc, flags);
		tile_at(x, y).flags = flags;

		x++;
	}
}

void t_tilebuffer::set_blank(int x, int y)
{
	if_inside_bounds(x, y)
		tile_at(x, y).set_blank();
}

t_tile& t_tilebuffer::get_ref(int x, int y)
{
	return tile_at(x, y);
}

t_tile t_tilebuffer::get_copy(int x, int y) const
{
	return tile_at(x, y);
}

void t_tilebuffer::fill(const t_tile& tile)
{
	for (int i = 0; i < length; i++)
		tiles[i] = tile;
}

void t_tilebuffer::clear()
{
	for (int i = 0; i < length; i++)
		tiles[i].set_blank();
}

t_list<t_tile>& t_tilebuffer::get_tiles()
{
	return tiles;
}

t_sprite_ptr t_tilebuffer::get_cursor()
{
	return cursor_sprite;
}

int t_tilebuffer::get_loaded_back_color() const
{
	return loaded_back_color;
}

void t_tilebuffer::save(const t_string& filename, int back_color)
{
	t_record_file file;
	file.open(filename, t_filesystem::write_mode);

	file.write(USR_WIDTH);
	file.write(USR_HEIGHT);
	file.write(LAYER_COUNT);
	file.write(back_color);

	for (int y = 0; y < USR_HEIGHT; y++) {
		for (int x = 0; x < USR_WIDTH; x++) {
			
			t_tile& tile = get_ref(x, y);
			bool has_object = tile.is_not_blank();
			file.write(has_object);

			if (has_object) {

				bool transparent = false;
				file.write(transparent);

				int anim_size = tile.get_all_chars().size();
				file.write(anim_size);

				for (int i = 0; i < anim_size; i++) {
					int ch = tile.get_char(i).ix;
					int fgc = tile.get_char(i).fgc;
					int bgc = tile.get_char(i).bgc;
					file.write(ch);
					file.write(fgc);
					file.write(bgc);
				}

				int prop_count = tile.data.size();
				file.write(prop_count);

				for (auto& item : tile.data.get_all()) {
					file.write(item.first);
					file.write(item.second);
				}
			}
		}
	}

	file.close_and_save();
}

bool t_tilebuffer::load(const t_string& filename)
{
	t_record_file file;
	if (file.open(filename, t_filesystem::read_mode) != RECFILE_STATE_OK)
		return false;

	clear();

	int width = file.read_int();
	int height = file.read_int();
	int layers = file.read_int();

	loaded_back_color = file.read_int();

	fill(t_tile(0, 0, loaded_back_color));

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			t_tile tile(0, 0, loaded_back_color);

			bool has_object = file.read_int() == 1;
			if (has_object) {
				
				tile.delete_all_chars();

				bool transparent = file.read_int() == 1;

				int anim_size = file.read_int();
				for (int i = 0; i < anim_size; i++) {
					int ix = file.read_int();
					int fgc = file.read_int();
					int bgc = file.read_int();
					tile.add_char(ix, fgc, bgc);
				}

				int prop_count = file.read_int();
				for (int i = 0; i < prop_count; i++) {
					t_string&& key = file.read();
					t_string&& value = file.read();
					tile.data.set(key, value);
				}
			}

			set(tile, x, y);
		}
	}

	return true;
}
