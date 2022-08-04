#pragma once
#include "common.h"
#include "t_variable.h"
#include "t_table.h"

struct t_performance_monitor;

struct t_machine {
	// Debugging
	t_performance_monitor* perfmon = nullptr;
	// Namespaces
	std::map<string, t_variable> vars;
	std::map<string, TTileSeq> tilestore;
	std::map<string, std::vector<string>> arrays;
	std::map<string, t_table> tables;
	// Graphics
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
	static const int default_bgc = 0;
	static const int default_fgc = 1;
	int bgcolor_palette_ix = default_bgc;
	TTileBuffer* tilebuf;
	TTileSeq cur_tile;
	bool tile_transparency = false;
	struct {
		int fg = 1;
		int bg = 0;
	} text_color;
	// Input
	SDL_Keycode last_key_pressed = 0;
	SDL_Keycode exit_key = SDLK_ESCAPE;
	// Sound
	TSound* snd = nullptr;
	// Latest comparison result
	int cmp_result = 0;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();
	void on_screen_update();
	void init_system_vars();
	void set_var(string id, int value);
	void set_var(string id, string value);
	void set_const(string id, int value);
	void set_const(string id, string value);
	void put_tile_at_cursor_pos(TTileSeq& tile);
	void put_cur_tile_at_cursor_pos();
	void copy_tile_at_cursor_pos();
	void delete_tile_at_cursor_pos();
	void set_window_bgcolor(int palette_ix);
	void set_cursor_pos(int x, int y);
	void move_cursor(int dx, int dy);
	void draw_cursor();
	void erase_cursor();
	int get_csr_layer();
	int get_csr_x();
	int get_csr_y();
	void set_csr_layer(int layer);
	void set_csr_color(int color);
	void set_csr_visible(bool visible);
	bool is_valid_tileseq(TTileSeq& tileseq);
	bool is_valid_tile(const TTile& tile);
	bool is_valid_charset_ix(int ix);
	bool is_valid_palette_ix(int ix);
	bool is_valid_char_def(int row_ix, int data);
	bool is_valid_color_rgb(int rgb);

private:
	TCharset* original_chr;
	TPalette* original_pal;
	struct {
		bool visible = false;
		TTileSeq tile;
		int color = default_fgc;
		int layer = 0;
		int x = 0;
		int y = 0;
	} csr;
};
