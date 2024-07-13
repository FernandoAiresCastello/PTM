#include "t_screen.h"
#include "t_tilebuffer.h"
#include "t_palette.h"
#include "t_charset.h"

t_screen::t_screen() : 
	buf(std::make_unique<t_tilebuffer>(cols, rows)),
	buf_reg(t_tilebuffer_region(0, 0, t_window::cols - 4, t_window::rows - 2))
{
	reset();
}

void t_screen::reset()
{
	color(default_fg, default_bg, default_bdr);
	clear();
	init_cursor();
	update_monochrome_tiles();
	show_cursor(true);
	locate(0, 0);
	logical_line = t_string::repeat(" ", cols);
}

void t_screen::init_cursor()
{
	t_tile cursor_tile = t_tile(127, 0, 0, t_tileflags());
	csr = buf->add_sprite(cursor_tile, t_pos(0, 0));
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
	clear_background();
	buf->draw(wnd, chr, pal, buf_pos, buf_reg);

	wnd->set_title(t_string::fmt("X:%i Y:%i O:%i", csr->pos.x, csr->pos.y, buf_reg.offset_x));
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

void t_screen::set_color_mode(t_color_mode color_mode)
{
	this->color_mode = color_mode;
	if (color_mode == t_color_mode::mode0_monochrome)
		update_monochrome_tiles();
}

void t_screen::clear_background()
{
	wnd->clear(pal->get(border_color));
}

void t_screen::color(t_index fgc, t_index bgc, t_index bdrc)
{
	fore_color = fgc;
	back_color = bgc;
	border_color = bdrc;
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
	update_monochrome_tiles();
}

void t_screen::locate(int x, int y)
{
	set_insert_mode(false);
	csr->move_to(x, y);
	fix_cursor_pos();
}

void t_screen::move_cursor_dist(int dx, int dy)
{
	set_insert_mode(false);
	csr->move_dist(dx, dy);
	fix_cursor_pos();
}

void t_screen::move_cursor_wrap_x(int dx)
{
	set_insert_mode(false);

	if (dx < 0 && csr->pos.x == 0 && csr->pos.y == 0)
		return;
	if (dx > 0 && csr->pos.x == last_col && csr->pos.y == last_row)
		return;

	csr->move_dist(dx, 0);
	
	if (csr->pos.x > last_col)
		csr->move_to(0, csr->pos.y + 1);
	else if (csr->pos.x < 0)
		csr->move_to(last_col, csr->pos.y - 1);

	fix_cursor_pos();
}

void t_screen::move_cursor_top_left()
{
	set_insert_mode(false);
	csr->move_to(0, 0);
}

void t_screen::move_cursor_btm_right()
{
	locate(last_col, last_row);
}

void t_screen::move_cursor_line_start()
{
	locate(0, csry());
}

void t_screen::move_cursor_eol()
{
	locate(eol(), csry());
}

void t_screen::fix_cursor_pos()
{
	if (csr->get_x() < 0)				csr->set_x(0);
	else if (csr->get_x() > last_col)	csr->set_x(last_col);
	if (csr->get_y() < 0)				csr->set_y(0);
	else if (csr->get_y() > last_row)	csr->set_y(last_row);
}

void t_screen::update_cursor()
{
	if (!insert_mode) {
		t_char& csr_char = csr->tile.get_char();
		csr_char.ix = get_tile_at_csr().get_char().ix;
		csr_char.fgc = back_color;
		csr_char.bgc = fore_color;
	}
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
	int x = last_col;
	int y = csr->get_y();

	for (x; x >= 0; x--) {
		t_tile& tile = buf->get_ref(x, y);
		if (tile.get_char().ix != 0 || tile.data.is_not_empty())
			break;
	}

	return x == last_col ? x : x + 1;
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

void t_screen::set_blank_tile_at_csr(t_tileflags flags)
{
	set_blank_tile(csr->pos.x, csr->pos.y, flags);
}

void t_screen::set_whitespace_at_csr(t_tileflags flags)
{
	auto& tile = buf->get_ref(csr->pos.x, csr->pos.y);
	tile.set_blank();
	tile.set_char(' ', fore_color, back_color);
	tile.flags = flags;
}

void t_screen::print_char(t_index ch)
{
	if (insert_mode)
		displace_tiles_right();

	print_tile(t_tile(ch, fore_color, back_color));
}

void t_screen::print_tile(const t_tile& tile)
{
	buf->set(tile, csr->get_x(), csr->get_y());

	csr->move_dist(1, 0);
	if (csr->pos.x > last_col) {
		csr->pos.x = 0;
		csr->pos.y++;
		if (csr->pos.y > last_row) {
			csr->pos.y = last_row;
			csr->pos.x = 0;
			scroll_up();
		}
	}
}

void t_screen::print_string(const t_string& str)
{
	int ix = buf->set_text_wrap(str, &csr->pos.x, &csr->pos.y, fore_color, back_color);

	if (csr->pos.y > last_row) {
		csr->pos.y = last_row;
		csr->pos.x = 0;
		scroll_up();
		print_string(str.substr(ix));
	}
}

void t_screen::print_string_crlf(const t_string& str)
{
	print_string(str);
	newline();
}

void t_screen::print_lines(const t_list<t_string>& lines)
{
	for (auto& str : lines) {
		print_string_crlf(str);
	}
}

void t_screen::newline()
{
	set_insert_mode(false);

	csr->pos.x = 0;
	csr->pos.y++;
	if (csr->pos.y > last_row) {
		csr->pos.y = last_row;
		scroll_up();
	}
}

void t_screen::scroll_up()
{
	for (int row = 1; row <= last_row; row++) {
		for (int col = 0; col <= last_col; col++) {
			buf->set(buf->get_ref(col, row), col, row - 1);
		}
	}

	int row = last_row;
	for (int col = 0; col <= last_col; col++) {
		set_blank_tile(col, row, t_tileflags());
	}
}

void t_screen::scroll_horizontal(int dist)
{
	buf_reg.offset_x += dist;
	if (buf_reg.offset_x < 0)
		buf_reg.offset_x = 0;
	else if (buf_reg.offset_x > cols - buf_reg.width)
		buf_reg.offset_x = cols - buf_reg.width;
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

void t_screen::update_monochrome_tiles()
{
	if (color_mode != t_color_mode::mode0_monochrome)
		return;

	for (int y = 0; y < buf->rows; y++)
		for (int x = 0; x < buf->cols; x++)
			update_monochrome_tile(buf->get_ref(x, y));

	for (const auto& spr : buf->get_sprites())
		update_monochrome_tile(spr->get_tile());
}

void t_screen::update_monochrome_tile(t_tile& tile) const
{
	if (!tile.flags.monochrome)
		return;
	if (color_mode != t_color_mode::mode0_monochrome)
		return;

	for (auto& ch : tile.get_all_chars()) {
		ch.fgc = fore_color;
		ch.bgc = back_color;
	}
}

t_string t_screen::get_current_logical_line()
{
	for (int x = 0; x < cols; x++) {
		t_tile& tile = get_tile(t_pos(x, csr->pos.y));
		t_index ch = tile.get_char().ix;
		if (ch <= 0 || ch > 255)
			ch = ' ';

		logical_line[x] = ch;
	}

	return logical_line.trim();
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

void t_screen::toggle_insert_mode()
{
	set_insert_mode(!insert_mode);
}

void t_screen::set_insert_mode(bool state)
{
	insert_mode = state;

	if (insert_mode) {
		t_tile tile('_', fore_color, back_color);
		tile.flags.hide_bgc = true;
		csr->set_tile(tile);
	}
	else {
		csr->set_tile(t_tile());
	}

	update_cursor();
}

void t_screen::displace_tiles_right()
{
}
