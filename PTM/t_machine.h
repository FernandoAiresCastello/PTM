#pragma once
#include "common.h"
#include "t_variable.h"

struct t_performance_monitor;
struct t_interpreter;

struct t_machine {
	t_interpreter* intp = nullptr;
	// Debugging
	t_performance_monitor* perfmon = nullptr;
	// Namespaces
	std::map<string, t_variable> vars;
	std::map<string, TTileSeq> tilestore;
	std::map<string, std::vector<string>> arrays;
	std::map<string, TTileBuffer*> tilebufs;
	// Graphics
	TBufferedWindow* wnd;
	TCharset* chr;
	TPalette* pal;
	static const int default_bgc = 0;
	static const int default_fgc = 1;
	int bgcolor_palette_ix = default_bgc;
	TTileBuffer* cur_buf;
	TTileSeq cur_tile;
	bool tile_transparency = false;
	struct {
		int fg = 1;
		int bg = 0;
	} text_color;
	// Input
	SDL_Keycode exit_key = SDLK_ESCAPE;
	int last_key_pressed = 0;
	// Sound
	TSound* snd = nullptr;
	// Latest comparison result
	int cmp_result = 0;
	// Timing
	int clock = 0;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();
	void on_screen_update();
	void init_system_vars();
	std::vector<string> get_debug_info();
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
	int get_csr_layer();
	int get_csr_x();
	int get_csr_y();
	void set_csr_layer(int layer);
	bool is_valid_tileseq(TTileSeq& tileseq);
	bool is_valid_tile(const TTile& tile);
	bool is_valid_charset_ix(int ix);
	bool is_valid_palette_ix(int ix);
	bool is_valid_char_def(int row_ix, int data);
	bool is_valid_color_rgb(int rgb);
	string read_input_string(int maxlen);
	void move_tile_at_cursor_pos(int dx, int dy);
	void move_tile_block(int x, int y, int w, int h, int dx, int dy);

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
