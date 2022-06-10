#include "t_editor_screen_line.h"

void t_editor_screen_line::clear() {
	tiles.clear();
}
int t_editor_screen_line::length() {
	return tiles.size();
}
string t_editor_screen_line::text() {
	string chars = "";
	for (auto& tile : tiles) {
		if (!tile.IsEmpty()) {
			int ch = tile.GetChar(0);
			chars += (ch >= 32 && ch < 127) ? ch : 32;
		}
	}
	return chars;
}
void t_editor_screen_line::overwrite(int ix, TTileSeq ch) {
	if (ix >= tiles.size()) {
		tiles.push_back(ch);
	} else {
		tiles[ix] = ch;
	}
}
void t_editor_screen_line::overwrite(int ix, string chars, ixp fgc, ixp bgc) {
	for (auto& ch : chars) {
		auto tile = TTileSeq(ch, fgc, bgc);
		if (ix >= tiles.size()) {
			tiles.push_back(tile);
		} else {
			tiles[ix] = tile;
		}
	}
}
void t_editor_screen_line::insert(int ix, TTileSeq ch) {
	tiles.insert(tiles.begin() + ix, ch);
}
void t_editor_screen_line::insert(int ix, string chars, ixp fgc, ixp bgc) {
	for (auto& ch : chars) {
		tiles.insert(tiles.begin() + ix, TTileSeq(ch, fgc, bgc));
	}
}
void t_editor_screen_line::erase(int ix) {
	tiles.erase(tiles.begin() + ix);
}
void t_editor_screen_line::backspace(int ix) {
}
string t_editor_screen_line::linebrk(int ix) {
	return "";
}
