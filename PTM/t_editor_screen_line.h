#pragma once
#include "common.h"

struct t_editor_screen_line {
	void clear();
	int length();
	string text();
	void overwrite(int ix, TTileSeq ch);
	void overwrite(int ix, string chars, ixp fgc, ixp bgc);
	void insert(int ix, TTileSeq ch);
	void insert(int ix, string chars, ixp fgc, ixp bgc);
	void erase(int ix);
	void backspace(int ix);
	string linebrk(int ix);
	TTileSeq& get_tile(int ix);
private:
	std::vector<TTileSeq> tiles;
};
