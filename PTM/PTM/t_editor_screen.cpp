#include "t_editor_screen.h"

t_editor_screen::t_editor_screen(TBufferedWindow* wnd) {
	this->wnd = wnd;
	wnd_buf = wnd->GetBuffer();
	palette = wnd->GetPalette();
	charset = wnd->GetCharset();
	cols = wnd_buf->Cols;
	rows = wnd_buf->Rows;
	last_col = cols - 1;
	last_row = rows - 1;
	csr.x = 0;
	csr.y = 0;
	color.fg = 15;
	color.bg = 0x52;
	color.bdr = 0x56;
	first_line_ix = 0;
	first_char_ix = 0;
	max_visible_lines = rows - 2;
	max_visible_chars = cols - 2;
}
void t_editor_screen::clear_lines() {
	lines.clear();
	lines.push_back(t_editor_screen_line());
	csr_home();
	update();
}
void t_editor_screen::clear_current_line() {
	get_current_line().clear();
	csr.x = 0;
	update();
}
void t_editor_screen::update() {
	wnd->SetBackColor(color.bg);
	clear_wbuf();
	draw_border();
	draw_lines();
}
void t_editor_screen::clear_wbuf() {
	wnd_buf->ClearAllLayers();
}
void t_editor_screen::draw_border() {
	TTileSeq tile(0, color.fg, color.bdr);
	for (int ybuf = 0; ybuf < rows; ybuf++) {
		wnd_buf->SetTile(tile, 0, 0, ybuf, false);
		wnd_buf->SetTile(tile, 0, last_col, ybuf, false);
	}
	for (int xbuf = 0; xbuf < cols; xbuf++) {
		wnd_buf->SetTile(tile, 0, xbuf, 0, false);
		wnd_buf->SetTile(tile, 0, xbuf, last_row, false);
	}
}
void t_editor_screen::draw_lines() {
	int ix = first_line_ix;
	for (int ybuf = 1; ybuf <= last_row; ybuf++) {
		if (ix >= first_line_ix + max_visible_lines || ix >= lines.size()) {
			break;
		}
		draw_line(lines[ix], ybuf);
		ix++;
	}
}
void t_editor_screen::draw_line(t_editor_screen_line& line, int ybuf) {
	int x = 1;
	string text = line.text();
	TTileSeq tile;
	if (text.empty() && csr.y == ybuf - 1) {
		tile.Add(0, color.bg, color.fg);
		tile.Add(0, color.fg, color.bg);
		wnd_buf->SetTile(tile, 0, x, ybuf, false);
	} else {
		for (int i = first_char_ix; i < line.length(); i++) {
			ixc ch = line.text()[i];
			tile.Clear();
			if (x - 1 == csr.x && ybuf - 1 == csr.y && csr.x) {
				tile.Add(ch, color.bg, color.fg);
				tile.Add(ch, color.fg, color.bg);
			} else {
				tile.Add(ch, color.fg, color.bg);
			}
			wnd_buf->SetTile(tile, 0, x, ybuf, false);
			x++;
			if (x >= last_col) {
				return;
			}
		}
		if (csr.y == ybuf - 1 && csr.x >= text.length()) {
			tile.Clear();
			tile.Add(0, color.bg, color.fg);
			tile.Add(0, color.fg, color.bg);
			wnd_buf->SetTile(tile, 0, x, ybuf, false);
		}
	}
}
void t_editor_screen::csr_move(int dx, int dy) {
	if (csr.x + dx >= 0 && csr.x + dx <= get_current_line().length()) {
		csr.x += dx;
	}
	if (csr.y + dy >= 0 && csr.y + dy < lines.size()) {
		csr.y += dy;
	}
	update();
}
void t_editor_screen::csr_backspace() {
	if (csr.x > 0) {
		csr.x--;
		csr_delete();
	}
}
void t_editor_screen::csr_delete() {
	auto& line = get_current_line();
	if (csr.x < line.length()) {
		line.erase(csr.x);
		update();
	}
}
void t_editor_screen::csr_home() {
	csr.x = 0;
	csr.y = 0;
	first_line_ix = 0;
	update();
}
void t_editor_screen::csr_line_start() {
	csr.x = 0;
	update();
}
void t_editor_screen::csr_line_end() {
	csr.x = get_current_line().length();
	update();
}
void t_editor_screen::csr_end() {
	csr.y = lines.size() - 1;
	csr.x = get_current_line().length();
	update();
}
int t_editor_screen::csr_x() {
	return csr.x;
}
int t_editor_screen::csr_y() {
	return csr.y;
}
void t_editor_screen::crlf() {
	if (is_cursor_on_last_line()) {
		new_line();
	} else {
		next_line();
	}
}
t_editor_screen_line& t_editor_screen::get_current_line() {
	return lines[csr.y];
}
string t_editor_screen::get_current_string() {
	return lines[csr.y].text();
}
void t_editor_screen::new_line() {
	t_editor_screen_line line;
	lines.push_back(line);
	csr.x = 0;
	csr.y++;
	update();
}
void t_editor_screen::next_line() {
	csr.x = 0;
	csr.y++;
	update();
}
void t_editor_screen::type_char(ixc ch, bool overwrite, bool must_update) {
	if (ch == '\n') {
		crlf();
	}
	else {
		TTileSeq tile(ch, color.fg, color.bg);
		if (csr.y >= lines.size()) {
			new_line();
			csr.y--;
		}
		if (overwrite) {
			lines[csr.y].overwrite(csr.x++, tile);
		} else {
			lines[csr.y].insert(csr.x++, tile);
		}
	}
	if (must_update) {
		update();
	}
}
void t_editor_screen::print(string str, bool overwrite) {
	for (auto& ch : str) {
		type_char(ch, overwrite, false);
	}
	update();
}
void t_editor_screen::println(string str, bool overwrite) {
	print(str + "\n", overwrite);
}
void t_editor_screen::debug(string str) {
	int x = 1;
	int y = 0;
	for (auto& ch : str) {
		wnd_buf->SetTile(TTileSeq(ch, color.fg, color.bdr), 0, x, y, false);
		x++;
	}
}
int t_editor_screen::line_count() {
	return lines.size();
}
bool t_editor_screen::is_cursor_on_last_line() {
	return csr.y == lines.size() - 1;
}
void t_editor_screen::scroll_right() {
	first_char_ix++;
	update();
}
