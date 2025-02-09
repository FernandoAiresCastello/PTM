#include <SDL.h>
#include "t_screen.h"
#include "PTM.h"
#include "t_tilebuffer.h"
#include "t_palette.h"
#include "t_charset.h"
#include "predefined_charset_ix.h"

t_screen::t_screen(int cols, int rows) :
	cols(cols), rows(rows), last_col(cols - 1), last_row(rows - 1),
	buf(std::make_unique<t_tilebuffer>(cols, rows)),
	viewport(t_tilebuffer_region(0, 0, t_window::cols - 4, t_window::rows - 2))
{
	csr = buf->get_cursor();
	reset();
}

void t_screen::reset()
{
	color_mode = t_color_mode::mode0_monochrome;
	delete_all_sprites();
	color(default_fg, default_bg, default_bdr);
	clear();
	update_monochrome_tiles();
	show_cursor(true);
	locate(0, 0);
	logical_line = t_string::repeat(" ", cols);
	reset_horizontal_scroll();
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
	buf->draw(wnd, chr, pal, buf_pos, viewport);
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

void t_screen::reset_horizontal_scroll()
{
	viewport.offset_x = 0;
}

void t_screen::reset_vertical_scroll()
{
	viewport.offset_y = 0;
}

void t_screen::sync_horizontal_scroll()
{
	if (csr->get_x() < viewport.offset_x)
		viewport.offset_x = csr->get_x();
	else if (csr->get_x() >= viewport.offset_x + viewport.width)
		viewport.offset_x = csr->get_x() - viewport.width + 1;
}

void t_screen::sync_vertical_scroll()
{
	if (csr->get_y() < viewport.offset_y)
		viewport.offset_y = csr->get_y();
	else if (csr->get_y() >= viewport.offset_y + viewport.height)
		viewport.offset_y = csr->get_y() - viewport.height + 1;
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
	csr->move_to(x, y);
	fix_cursor_pos();
}

void t_screen::move_cursor_dist(int dx, int dy)
{
	csr->move_dist(dx, dy);
	fix_cursor_pos();
}

void t_screen::move_cursor_top_left()
{
	locate(0, 0);
}

void t_screen::move_cursor_line_start()
{
	locate(0, csry());
}

void t_screen::move_cursor_eol()
{
	locate(eol(), csry());
}

void t_screen::move_cursor_next_logical_x(int dist)
{
	while (true) {
		move_cursor_dist(dist, 0);
		const t_index& ch = get_tile_at_csr().get_char().ix;
		if (ch == 0 || ch == ' ' || ch == ',')
			break;
		if (csr->get_x() == 0 || csr->get_x() == last_col)
			break;
	}
}

void t_screen::fix_cursor_pos()
{
	if (csr->get_x() < 0)				csr->set_x(0);
	else if (csr->get_x() > last_col)	csr->set_x(last_col);
	if (csr->get_y() < 0)				csr->set_y(0);
	else if (csr->get_y() > last_row)	csr->set_y(last_row);

	sync_horizontal_scroll();
	sync_vertical_scroll();
}

void t_screen::update_cursor()
{
	if (!insert_mode && !printing_lines) {
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

t_tile t_screen::create_blank_tile(t_tileflags flags)
{
	auto&& tile = t_tile(0, fore_color, back_color);
	tile.flags = flags;
	return tile;
}

void t_screen::on_character_key_pressed(t_index ch)
{
	bool should_print = true;
	if (insert_mode)
		should_print = displace_tiles_right();
	if (should_print)
		print_char(ch);

	sync_horizontal_scroll();
}

void t_screen::on_backspace_pressed()
{
	if (csr->get_x() == 0)
		return;

	csr->move_dist(-1, 0);
	set_blank_tile_at_csr();
	displace_tiles_left();
}

void t_screen::on_delete_pressed()
{
	set_blank_tile_at_csr();
	displace_tiles_left();
}

void t_screen::print_char(t_index ch)
{
	if (csr->get_x() < last_col) {
		buf->set(t_tile(ch, fore_color, back_color), csr->pos.x, csr->pos.y);
		csr->move_dist(1, 0);
	}
}

void t_screen::print_tile(const t_tile& tile)
{
	if (csr->get_x() < last_col) {
		buf->set(tile, csr->pos.x, csr->pos.y);
		csr->move_dist(1, 0);
	}
}

void t_screen::print_string(const t_string& str)
{
	buf->set_text(str, csr->pos.x, csr->pos.y, fore_color, back_color);
	move_cursor_dist(str.length(), 0);
}

void t_screen::print_string_crlf(const t_string& str, bool allow_scroll)
{
	print_string(str);
	newline(allow_scroll);
}

void t_screen::print_string_at(const t_string& str, int x, int y)
{
	buf->set_text(str, x, y, fore_color, back_color);
}

bool t_screen::print_lines(const t_list<t_string>& lines, PTM* ptm)
{
	printing_lines = true;
	t_char& csr_ch = csr->tile.get_char();
	t_index prev_ch = csr_ch.ix;
	t_index prev_fg = csr_ch.fgc;
	t_index prev_bg = csr_ch.bgc;

	bool escaped = false;
	int lines_printed = 0;

	for (const auto& line : lines) {
		print_string_crlf(line);
		lines_printed++;
		if (lines_printed >= last_row - 2) {
			SDL_Keycode key = 0;
			while (key != SDLK_RETURN && key != SDLK_ESCAPE) {
				csr_ch.ix = predef_char.enter_symbol;
				csr_ch.fgc = prev_fg;
				csr_ch.bgc = prev_bg;

				key = ptm->await_keypress();
				if (key == SDLK_RETURN)
					continue;
				if (key == SDLK_ESCAPE) {
					escaped = true;
					break;
				}
			}
		}
		if (escaped)
			break;
	}

	printing_lines = false;
	csr_ch.ix = prev_ch;
	csr_ch.fgc = prev_fg;
	csr_ch.bgc = prev_bg;

	return escaped;
}

bool t_screen::print_lines_with_icon(const t_list<t_tile>& icons, const t_list<t_string>& lines, PTM* ptm)
{
	bool escaped = false;
	int lines_printed = 0;
	int icon_index = 0;
	for (const auto& line : lines) {
		if (icon_index < icons.size())
			print_tile(icons[icon_index++]);

		print_string_crlf(line);
		lines_printed++;
		if (lines_printed >= last_row) {
			SDL_Keycode key = 0;
			while (key != SDLK_RETURN && key != SDLK_ESCAPE) {
				key = ptm->await_keypress();
				if (key == SDLK_RETURN)
					continue;
				if (key == SDLK_ESCAPE) {
					escaped = true;
					break;
				}
			}
		}
		if (escaped)
			break;
	}
	return escaped;
}

void t_screen::print_debug(const t_string& str)
{
	wnd->draw_debug_text(chr, str, 0, wnd->last_row);
}

void t_screen::newline(bool allow_scroll)
{
	set_insert_mode(false);
	reset_horizontal_scroll();

	csr->pos.x = 0;
	csr->pos.y++;
	if (csr->pos.y > last_row) {
		csr->pos.y = last_row;
		if (allow_scroll) {
			scroll_up_for_text_editor();
		}
	}
}

void t_screen::scroll_up_for_text_editor()
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

	sync_horizontal_scroll();
}

void t_screen::scroll_vertical(int dist)
{
	viewport.offset_y += dist;
	fix_vertical_scroll();
}

void t_screen::scroll_horizontal(int dist)
{
	viewport.offset_x += dist;
	fix_horizontal_scroll();
}

void t_screen::scroll_to(int x, int y)
{
	viewport.offset_x = x;
	viewport.offset_y = y;
	fix_horizontal_scroll();
	fix_vertical_scroll();
}

void t_screen::fix_horizontal_scroll()
{
	if (viewport.offset_x < 0)
		viewport.offset_x = 0;
	else if (viewport.offset_x > cols - viewport.width)
		viewport.offset_x = cols - viewport.width;
}

void t_screen::fix_vertical_scroll()
{
	if (viewport.offset_y < 0)
		viewport.offset_y = 0;
	else if (viewport.offset_y > rows - viewport.height)
		viewport.offset_y = rows - viewport.height;
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

bool t_screen::is_cursor_on_logical_line()
{
	return csr->get_y() >= 0 && csr->get_y() <= last_row;
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

	update_monochrome_tile(buf->get_cursor()->get_tile());
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
		if (ch < 32 || ch > 127)
			ch = predef_char.whitespace;

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
	bool csr_visible = csr->tile.flags.visible;

	if (insert_mode) {
		t_tile tile(predef_char.half_cursor, fore_color, back_color);
		tile.flags.hide_bgc = true;
		tile.flags.visible = csr_visible;
		csr->set_tile(tile);
	}
	else {
		csr->set_tile(t_tile());
		csr->set_visible(csr_visible);
	}

	update_cursor();
}

bool t_screen::displace_tiles_right()
{
	int y = csr->get_y();
	int x = eol() - 1;
	if (x >= last_col - 1)
		return false;

	while (x >= csr->get_x()) {
		auto&& tile_to_displace = buf->get_copy(x, y);
		buf->set(tile_to_displace, x + 1, y);
		x--;
	}

	return true;
}

bool t_screen::displace_tiles_left()
{
	int y = csr->get_y();
	int x = csr->get_x() + 1;

	while (x <= eol()) {
		auto&& tile_to_displace = buf->get_copy(x, y);
		buf->set(tile_to_displace, x - 1, y);
		x++;
	}

	return true;
}

const t_tilebuffer_region& t_screen::get_viewport()
{
	return viewport;
}

void t_screen::delete_all_sprites()
{
	buf->delete_all_sprites();
}

void t_screen::save(const t_string& filename)
{
	buf->save(filename, back_color);
}

void t_screen::load(const t_string& filename)
{
	bool ok = buf->load(filename);
	if (!ok) return;

	int new_back_color = buf->get_loaded_back_color();
	if (new_back_color >= 0)
		back_color = new_back_color;
}
