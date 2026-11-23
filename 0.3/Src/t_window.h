#pragma once
#include "t_color.h"
#include "t_string.h"
#include "t_index.h"
#include "t_tile.h"
#include "t_binary.h"
#include "t_tile_animation.h"
#include "t_pointers.h"

class t_charset;
class t_palette;
class t_image;

class t_window
{
public:
	void open(int img_w, int img_h, int wnd_zoom);
	void close();
	bool is_open();
	void toggle_fullscreen();
	void set_fullscreen(bool full);
	bool is_fullscreen() const;
	void set_title(const t_string& title);
	void clear(const t_color& color);
	void refresh();
	void reset_frame_counter();
	uint32_t get_frame_count() const;
	int get_animation_frame() const;
	void draw_pixel(int x, int y, const t_color& color);
	void draw_pixels(const t_binary& pixels, int x, int y, const t_color& color1, const t_color& color0, bool grid, bool hide_color0);
	void draw_char(t_charset* chr, t_palette* pal, t_index char_index, int x, int y, t_index color1, t_index color0, bool grid, bool hide_color0);
	void draw_text(t_charset* chr, t_palette* pal, const t_string& text, int x, int y, t_index color1, t_index color0, bool grid, bool hide_color0);
	void draw_debug_text(t_charset* chr, const t_string& text, int x, int y);
	void draw_image(t_image* image, int x, int y);
	int get_cols();
	int get_rows();

private:
	int image_w = 0;
	int image_h = 0;
	int cols = 0;
	int rows = 0;
	int last_col = 0;
	int last_row = 0;
	int window_zoom = 0;
	int buflen = 0;

	static constexpr bool stretch_fullscreen = true;
	static constexpr int tilesize = t_tile::width * t_tile::height;

	void* wnd = nullptr;
	void* rend = nullptr;
	void* tex = nullptr;
	bool fullscreen = false;
	t_uptr<t_rgb[]> scrbuf = nullptr;
	t_tile_animation tile_anim;
	uint32_t frame_counter = 0;
};
