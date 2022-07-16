#pragma once
#include "common.h"
#include "t_obj.h"

struct t_machine {
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
	std::map<string, string> vars;
	std::map<string, TTileSeq> saved_tiles;
	std::map<string, t_obj> objs;
	t_obj* cur_obj = nullptr;
	struct {
		int layer = 0;
		int x = 0;
		int y = 0;
	} csr;
	TTileBuffer* tilebuf;
	TTileSeq cur_tile;
	bool tile_transparency = false;
	bool auto_refresh = false;
	struct {
		int fg = 1;
		int bg = 0;
	} text_color;
	SDL_Keycode last_key_pressed = 0;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();

private:
	TCharset* original_chr;
	TPalette* original_pal;
};
