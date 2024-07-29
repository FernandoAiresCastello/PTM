#include <memory>
#include "t_tilebuffer.h"
#include "t_window.h"
#include "t_charset.h"
#include "t_palette.h"

#define tile_at(x, y)			tiles[y * cols + x]
#define if_inside_bounds(x, y)	if (x >= 0 && y >= 0 && x < cols && y < rows)
#define if_out_of_bounds(x, y)	if (x < 0 || y < 0 || x >= cols || y >= rows)

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
		t_tile(127, 0, 0, t_tileflags()), t_pos(0, 0), true);
}

void t_tilebuffer::draw(t_window* wnd, t_charset* chr, t_palette* pal, const t_pos& scr_pos, const t_tilebuffer_region& region)
{
	int px = 0;
	int py = 0;

	for (int y = region.offset_y; y < region.offset_y + region.height; y++) {
		for (int x = region.offset_x; x < region.offset_x + region.width; x++) {

			t_tile& tile = tile_at(x, y);
			draw_tile_absolute_pos(tile, wnd, chr, pal, scr_pos.x + px, scr_pos.y + py, true);

			if (cursor_sprite->get_x() == x && cursor_sprite->get_y() == y) {
				draw_tile_absolute_pos(cursor_sprite->get_tile(), wnd, chr, pal, scr_pos.x + px, scr_pos.y + py, true);
			}

			px++;
		}
		py++;
		px = 0;
	}

	draw_sprites(wnd, chr, pal);
}

void t_tilebuffer::draw_sprites(t_window* wnd, t_charset* chr, t_palette* pal)
{
	for (const auto& spr : sprites) {
		draw_tile_absolute_pos(spr->get_tile(), wnd, chr, pal, spr->get_x(), spr->get_y(), spr->align_to_grid());
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

t_sptr<t_sprite> t_tilebuffer::add_sprite(const t_tile& tile, const t_pos& pos, bool grid)
{
	t_sptr<t_sprite> sprite = sprites.emplace_back(std::make_shared<t_sprite>(tile, pos, grid));
	return sprite;
}

t_list<t_sptr<t_sprite>>& t_tilebuffer::get_sprites()
{
	return sprites;
}

void t_tilebuffer::delete_sprite(t_sptr<t_sprite> sprite)
{
	auto it = std::remove_if(sprites.begin(), sprites.end(),
		[&sprite](const std::shared_ptr<t_sprite>& ptr) {
			return ptr == sprite;
		}
	);
	sprites.erase(it, sprites.end());
}

void t_tilebuffer::delete_all_sprites()
{
	sprites.clear();
}

t_sptr<t_sprite> t_tilebuffer::get_cursor()
{
	return cursor_sprite;
}
