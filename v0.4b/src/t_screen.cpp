#include "t_screen.h"
#include "t_tilebuffer.h"
#include "t_palette.h"
#include "t_charset.h"

#define border_tile		t_tile(0, border_color, border_color)

t_screen::t_screen()
{
	buf = std::make_unique<t_tilebuffer>(t_window::cols - 4, t_window::rows - 2, true);
	buf_bdr = std::make_unique<t_tilebuffer>();
	buf_bdr->fill(border_tile);

	for (int y = 0; y < buf->rows; y++) {
		for (int x = 0; x < buf->cols; x++) {
			buf->get_ref(x, y).flags.monochrome = true;
		}
	}

	t_tile cursor_tile = t_tile(127, 0, 0);
	cursor_tile.flags.monochrome = true;
	cursor_tile.flags.hide_bgc = true;
	csr = add_tiled_sprite(cursor_tile, t_pos(0, 0));
	csr->set_visible(false);

	update_monochrome_tiles();
}

void t_screen::set_window(t_window* wnd)
{
	this->wnd = wnd;
}

void t_screen::set_charset(t_charset* chr)
{
	this->chr = chr;
}

void t_screen::set_palette(t_palette* pal)
{
	this->pal = pal;
}

void t_screen::draw()
{
	buf_bdr->draw(wnd, chr, pal);
	buf->draw(wnd, chr, pal, pos.x, pos.y);
	draw_sprites();
}

void t_screen::color(t_index fgc)
{
	fore_color = fgc;

	update_monochrome_tiles();
}

void t_screen::color(t_index fgc, t_index bgc)
{
	fore_color = fgc;
	back_color = bgc;

	update_monochrome_tiles();
}

void t_screen::color(t_index fgc, t_index bgc, t_index bdrc)
{
	fore_color = fgc;
	back_color = bgc;
	border_color = bdrc;

	buf_bdr->fill(border_tile);
	update_monochrome_tiles();
}

void t_screen::locate(int x, int y)
{
	csr->move_to(x, y);
	fix_cursor_pos();
}

void t_screen::move_cursor(int dx, int dy)
{
	csr->move_dist(dx, dy);
	fix_cursor_pos();
}

void t_screen::fix_cursor_pos()
{
	if (csr->get_x() < 0)			csr->set_x(0);
	if (csr->get_x() > last_col())	csr->set_x(last_col());
	if (csr->get_y() < 0)			csr->set_y(0);
	if (csr->get_y() > last_row())	csr->set_y(last_row());
}

int t_screen::last_row() const
{
	return buf->last_row();
}

int t_screen::last_col() const
{
	return buf->last_col();
}

int t_screen::csrx() const
{
	return csr->get_x();
}

int t_screen::csry() const
{
	return csr->get_y();
}

t_pos t_screen::csr_pos() const
{
	return csr->get_pos();
}

void t_screen::show_cursor(bool visible)
{
	csr->set_visible(visible);
}

void t_screen::set_tile(const t_tile& tile, int x, int y)
{
	buf->set(tile, x, y);
}

void t_screen::set_tile_overlay(const t_tile& tile, int x, int y)
{
	buf->set_overlay(tile, x, y);
}

void t_screen::set_blank_tile(int x, int y, t_tileflags flags)
{
	auto& tile = buf->get_ref(x, y);
	tile.set_blank();
	tile.set_char(0, fore_color, back_color);
	tile.flags = flags;
}

void t_screen::print(const t_tile& tile)
{
	buf->set(tile, csr->get_x(), csr->get_y());
	csr->move_dist(1, 0);

	if (csr->pos.x > last_col()) {
		csr->pos.x = 0;
		csr->pos.y++;
		if (csr->pos.y > last_row()) {
			csr->pos.y = last_row();
			csr->pos.x = 0;
			scroll_up();
		}
	}
}

void t_screen::print(const char& ch)
{
	buf->set(t_tile(ch, fore_color, back_color), csr->pos.x, csr->pos.y);
	csr->move_dist(1, 0);

	if (csr->pos.x > last_col()) {
		csr->pos.x = 0;
		csr->pos.y++;
		if (csr->pos.y > last_row()) {
			csr->pos.y = last_row();
			csr->pos.x = 0;
			scroll_up();
		}
	}
}

void t_screen::print(const t_string& str)
{
	t_tileflags flags = t_tileflags();
	flags.monochrome = true;

	int ix = buf->set_text_wrap(str, &csr->pos.x, &csr->pos.y, fore_color, back_color, flags);

	if (csr->pos.y > last_row()) {
		csr->pos.y = last_row();
		csr->pos.x = 0;
		scroll_up();
		print(str.substr(ix));
	}
}

void t_screen::println(const t_string& str)
{
	print(str);
	
	csr->pos.x = 0;
	csr->pos.y++;
	if (csr->pos.y > last_row()) {
		csr->pos.y = last_row();
		scroll_up();
	}
}

void t_screen::scroll_up()
{
	for (int row = 1; row <= last_row(); row++) {
		for (int col = 0; col <= last_col(); col++) {
			buf->set(buf->get_ref(col, row), col, row - 1);
		}
	}

	int row = last_row();
	for (int col = 0; col <= last_col(); col++) {
		t_tileflags flags = t_tileflags();
		flags.monochrome = true;
		set_blank_tile(col, row, flags);
	}
}

t_sptr<t_sprite> t_screen::add_free_sprite(const t_tile& tile, const t_pos& pos)
{
	return add_sprite(tile, pos, false);
}

t_sptr<t_sprite> t_screen::add_tiled_sprite(const t_tile& tile, const t_pos& pos)
{
	return add_sprite(tile, pos, true);
}

void t_screen::remove_sprite(t_sptr<t_sprite> sprite)
{
	auto it = std::remove_if(sprites.begin(), sprites.end(),
		[&sprite](const std::shared_ptr<t_sprite>& ptr) {
			return ptr == sprite;
		}
	);

	sprites.erase(it, sprites.end());
}

t_sptr<t_sprite> t_screen::add_sprite(const t_tile& tile, const t_pos& pos, bool grid)
{
	t_sptr<t_sprite> sprite = sprites.emplace_back(std::make_shared<t_sprite>(tile, pos, grid));
	update_monochrome_tile(sprite->get_tile());
	return sprite;
}

void t_screen::draw_sprites()
{
	for (auto& spr : sprites) {
		t_tile& tile = spr->get_tile();
		if (tile.flags.visible) {
			t_char& ch = tile.get_char_wraparound(wnd->get_animation_frame());
			bool grid = spr->align_to_grid();
			int x = grid ? (spr->get_x() + pos.x) * t_tile::width : spr->get_x(); 
			int y = grid ? (spr->get_y() + pos.y) * t_tile::height : spr->get_y();
			wnd->draw_char(chr, pal, ch.ix, x, y, ch.fgc, ch.bgc, false, spr->get_tile().flags.hide_bgc);
		}
	}
}

void t_screen::update_monochrome_tiles()
{
	for (int y = 0; y < buf->rows; y++) {
		for (int x = 0; x < buf->cols; x++) {
			update_monochrome_tile(buf->get_ref(x, y));
			update_monochrome_tile(buf->get_ref_overlay(x, y));
		}
	}

	for (auto& spr : sprites) {
		update_monochrome_tile(spr->get_tile());
	}
}

void t_screen::update_monochrome_tile(t_tile& tile) const
{
	if (tile.flags.monochrome) {
		for (auto& ch : tile.get_all_chars()) {
			ch.fgc = fore_color;
			ch.bgc = back_color;
		}
	}
}
