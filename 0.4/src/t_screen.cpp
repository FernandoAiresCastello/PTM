#include "t_screen.h"
#include "t_tilebuffer.h"
#include "t_palette.h"
#include "t_charset.h"

#define border_tile		t_tile(0, border_color, border_color, t_tileflags())

t_screen::t_screen()
{
	buf = std::make_unique<t_tilebuffer>(t_window::cols - 4, t_window::rows - 2);
	buf_bdr = std::make_unique<t_tilebuffer>();

	reset();
}

void t_screen::init_cursor()
{
	t_tile cursor_tile = t_tile(127, 0, 0, t_tileflags());
	csr = add_tiled_sprite(cursor_tile, t_pos(0, 0));
}

void t_screen::reset()
{
	color(default_fg, default_bg, default_bdr);
	buf_bdr->fill(border_tile);
	clear();
	sprites.clear();
	init_cursor();
	update_monochrome_tiles();
	show_cursor(true);
	locate(0, 0);
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

void t_screen::refresh()
{
	update_cursor();
	draw();
}

void t_screen::draw()
{
	buf_bdr->draw(wnd, chr, pal);
	buf->draw(wnd, chr, pal, pos.x, pos.y);
	draw_sprites();
}

void t_screen::clear()
{
	for (int y = 0; y < buf->rows; y++) {
		for (int x = 0; x < buf->cols; x++) {
			t_tile& tile = buf->get_ref(x, y);
			tile.set_blank();
			tile.flags.clear();
			tile.set_char(0, fore_color, back_color);
		}
	}
}

void t_screen::color(t_index fgc, t_index bgc, t_index bdrc)
{
	fore_color = fgc;
	back_color = bgc;
	border_color = bdrc;
	buf_bdr->fill(border_tile);
	update_monochrome_tiles();
}

void t_screen::color_fg(t_index fg)
{
	fore_color = fg;
	update_monochrome_tiles();
}

void t_screen::color_bg(t_index bg)
{
	back_color = bg;
	update_monochrome_tiles();
}

void t_screen::color_bdr(t_index bdr)
{
	border_color = bdr;
	buf_bdr->fill(border_tile);
	update_monochrome_tiles();
}

void t_screen::locate(int x, int y)
{
	csr->move_to(x, y);
	fix_cursor_pos();
}

void t_screen::move_cursor_dist(int dx, int dy)
{
	csr->move_dist(dx, dy);
	fix_cursor_pos();
}

void t_screen::move_cursor_wrap_x(int dx)
{
	if (dx < 0 && csr->pos.x == 0 && csr->pos.y == 0)
		return;
	if (dx > 0 && csr->pos.x == last_col() && csr->pos.y == last_row())
		return;

	csr->move_dist(dx, 0);
	
	if (csr->pos.x > last_col()) {
		csr->move_to(0, csr->pos.y + 1);
	}
	else if (csr->pos.x < 0) {
		csr->move_to(last_col(), csr->pos.y - 1);
	}

	fix_cursor_pos();
}

int t_screen::rows() const
{
	return buf->rows;
}

int t_screen::cols() const
{
	return buf->cols;
}

void t_screen::fix_cursor_pos()
{
	if (csr->get_x() < 0)				csr->set_x(0);
	else if (csr->get_x() > last_col())	csr->set_x(last_col());
	if (csr->get_y() < 0)				csr->set_y(0);
	else if (csr->get_y() > last_row())	csr->set_y(last_row());
}

void t_screen::update_cursor()
{
	t_char& csr_char = csr->tile.get_char();
	csr_char.ix = get_tile_at_csr().get_char().ix;
	csr_char.fgc = back_color;
	csr_char.bgc = fore_color;
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

int t_screen::eol() const
{
	int x = last_col();
	int y = csr->get_y();

	for (x; x >= 0; x--) {
		t_tile& tile = buf->get_ref(x, y);
		if (tile.get_char().ix != 0 || tile.data.is_not_empty())
			break;
	}

	return x == last_col() ? x : x + 1;
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

void t_screen::set_tile_at_csr(const t_tile& tile)
{
	buf->set(tile, csr->pos.x, csr->pos.y);
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
	if (csr->pos.x == last_col()) {
		buf->get_ref(csr->get_x(), csr->get_y()).flags.line_wrap = true;
	}
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

void t_screen::print(t_index ch)
{
	print(t_tile(ch, fore_color, back_color));
}

void t_screen::print(const t_string& str)
{
	int ix = buf->set_text_wrap(str, &csr->pos.x, &csr->pos.y, fore_color, back_color);

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
	newline();
}

void t_screen::print_lines(const t_list<t_string>& lines)
{
	for (auto& str : lines) {
		println(str);
	}
}

void t_screen::newline()
{
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
		set_blank_tile(col, row, t_tileflags());
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

t_tile& t_screen::get_tile(const t_pos& pos)
{
	return buf->get_ref(pos.x, pos.y);
}

t_tile& t_screen::get_tile_at_csr()
{
	return buf->get_ref(csr->pos.x, csr->pos.y);
}

void t_screen::set_csr_char_ix(t_index ch)
{
	csr->tile.get_char().ix = ch;
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
	for (int y = 0; y < buf->rows; y++)
		for (int x = 0; x < buf->cols; x++)
			update_monochrome_tile(buf->get_ref(x, y));

	for (auto& spr : sprites)
		update_monochrome_tile(spr->get_tile());
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

t_string t_screen::get_current_logical_line()
{
	t_string last_half;

	int y = csry();
	for (int x = csrx(); x <= last_col(); x++) {
		t_tile& tile = get_tile(t_pos(x, y));
		t_index ch = tile.get_char().ix;
		if (ch <= 0 || ch > 255)
			ch = ' ';

		last_half += ch;
		if (tile.flags.line_wrap) {
			x = -1;
			y++;
			if (y > last_row()) {
				break;
			}
		}
	}

	t_string first_half;

	y = csry();
	int x = csrx() - 1;
	for (x; x >= -1; x--) {
		if (x == -1) {
			x = last_col();
			y--;
			if (y < 0) {
				break;
			}
			t_tile& tile = get_tile(t_pos(x, y));
			if (!tile.flags.line_wrap) {
				break;
			}
		}
		t_tile& tile = get_tile(t_pos(x, y));
		t_index ch = tile.get_char().ix;
		if (ch <= 0 || ch > 255)
			ch = ' ';

		first_half += ch;
	}

	first_half = first_half.reverse();

	return t_string(first_half + last_half).trim();
}

t_index t_screen::get_fg_color() const
{
	return fore_color;
}

t_index t_screen::get_bg_color() const
{
	return back_color;
}

t_index t_screen::get_bdr_color() const
{
	return border_color;
}

void t_screen::fill(const t_tile& tile)
{
	buf->fill(tile);
}

void t_screen::rect_fill(const t_tile& tile, int x1, int y1, int x2, int y2)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++)
			set_tile(tile, x, y);
}

void t_screen::rect_border(const t_tile& tile, int x1, int y1, int x2, int y2)
{
	for (int x = x1; x <= x2; x++) {
		set_tile(tile, x, y1);
		set_tile(tile, x, y2);
	}
	for (int y = y1; y <= y2; y++) {
		set_tile(tile, x1, y);
		set_tile(tile, x2, y);
	}
}

void t_screen::rect_clear(int x1, int y1, int x2, int y2)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++)
			set_blank_tile(x, y);
}
