#pragma once
#include "common.h"
#include "t_variable.h"

struct t_machine {
	// Namespaces
	std::map<string, t_variable> vars;
	std::map<string, TTileSeq> tilestore;
	std::map<string, std::vector<string>> arrays;
	// Graphics
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
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
	// Input
	SDL_Keycode last_key_pressed = 0;
	// Sound
	TSound* snd = nullptr;
	// Comparisons
	int cmp_result = 0;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();
	void init_system_vars();
	void set_var(string id, int value);
	void set_var(string id, string value);
	void set_const(string id, int value);
	void set_const(string id, string value);
	void put_cur_tile_at_cursor_pos();

private:
	TCharset* original_chr;
	TPalette* original_pal;
};