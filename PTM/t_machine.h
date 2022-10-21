#pragma once
#include "common.h"
#include "t_variable.h"

struct t_performance_monitor;
struct t_interpreter;

struct t_machine {
	t_interpreter* intp = nullptr;
	// Debugging
	t_performance_monitor* perfmon = nullptr;
	bool show_perfmon = false;
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
	static const int default_fgc = 15;
	int bgcolor_palette_ix = default_bgc;
	TTileBuffer* cur_buf;
	TTileSeq cur_tile;
	bool tile_transparency = false;
	struct {
		int fg = default_fgc;
		int bg = default_bgc;
	} text_color;
	// Input
	SDL_Keycode exit_key = SDLK_ESCAPE;
	int last_keycode_pressed = 0;
	// Sound
	TSound* snd = nullptr;
	// Timing
	int clock = 0;

	t_machine(TBufferedWindow* wnd);
	~t_machine();
	void on_loop();
	void init_system_vars();
	std::vector<string> get_debug_info();
	void save_debug_file();
	void set_var(string id, int value);
	void set_var(string id, string value);
	void set_const(string id, int value);
	void set_const(string id, string value);
	void put_tile_at_cursor_pos(TTileSeq& tile);
	void add_tile_frame_at_cursor_pos(TTile& tile);
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
	void print_text(string text, bool crlf, bool add_frames);
	void draw_tile_sequence(string seq);
	std::vector<string> split_tile_sequence(std::string& seq);

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
