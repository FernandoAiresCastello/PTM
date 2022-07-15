#pragma once
#include "common.h"

struct t_machine {
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
	std::map<string, string> vars;
	std::map<string, TTileSeq> saved_tiles;
	struct {
		int layer = 0;
		int x = 0;
		int y = 0;
	} csr;
	TTileBuffer* tilebuf;
	TTileSeq cur_tile;
	bool tile_transparency = false;
	bool auto_refresh = false;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();

private:
	TCharset* original_chr;
	TPalette* original_pal;
};
