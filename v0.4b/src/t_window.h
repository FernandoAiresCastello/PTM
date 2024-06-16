#pragma once
#include "t_color.h"
#include "t_string.h"
#include "t_tile.h"
#include "t_binary.h"
#include "t_charset.h"
#include "t_tile_animation.h"

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
	void clear(const t_color& color);
	void update();
	void reset_frame_counter();
	uint32_t get_frame_count() const;
	int get_animation_frame() const;
	
	void draw_pixel(int x, int y, const t_color& color);
	void draw_pixels(const t_binary& pixels, int x, int y, const t_color& color1, const t_color& color0, bool grid);
	void draw_char(t_charset* charset, int char_index, int x, int y, const t_color& color1, const t_color& color0, bool grid);
	void draw_text(t_charset* charset, const t_string& text, int x, int y, const t_color& color1, const t_color& color0, bool grid);

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
