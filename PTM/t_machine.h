#pragma once
#include "common.h"
#include "t_view.h"

struct t_machine {
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
	std::map<string, string> vars;
	std::map<string, t_view> views;
	t_view* cur_view = nullptr;
	t_view default_view;
	struct {
		int layer = 0;
		int x = 0;
		int y = 0;
	} csr;
	TTileBuffer* tilebuf;
	TTileSeq cur_tile;
	bool tile_transparency = false;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();
	bool is_csr_within_view();

private:
	TCharset* original_chr;
	TPalette* original_pal;
};
