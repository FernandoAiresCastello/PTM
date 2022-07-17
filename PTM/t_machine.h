#pragma once
#include "common.h"
#include "t_variable.h"
#include "t_obj.h"

struct t_machine {
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
	std::map<string, t_variable> vars;
	std::map<string, TTileSeq> tilestore;
	std::map<string, t_obj> objs;
	struct {
		int layer = 0;
		int x = 0;
		int y = 0;
	} csr;
	TTileBuffer* tilebuf;
	TTileSeq cur_tile;
	bool tile_transparency = false;
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
