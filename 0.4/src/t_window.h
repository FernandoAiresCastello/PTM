#pragma once
#include "t_color.h"
#include "t_string.h"
#include "t_index.h"
#include "t_tile.h"
#include "t_binary.h"
#include "t_tile_animation.h"

class t_charset;
class t_palette;

class t_window
{
public:
	static constexpr int image_w = 360;
	static constexpr int image_h = 200;
	static constexpr int cols = image_w / t_tile::width;
	static constexpr int rows = image_h / t_tile::height;

	void open(const t_string& title, int size);
	void close();
	bool is_open();
	void toggle_fullscreen();
	void set_fullscreen(bool full);
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

private:
	static constexpr int tilesize = t_tile::width * t_tile::height;
	static constexpr int buflen = image_w * image_h * sizeof(t_rgb);

	void* wnd = nullptr;
	void* rend = nullptr;
	void* tex = nullptr;
	bool fullscreen = false;
	t_rgb scrbuf[buflen] = { 0 };
	t_tile_animation tile_anim;
	uint32_t frame_counter = 0;
};
