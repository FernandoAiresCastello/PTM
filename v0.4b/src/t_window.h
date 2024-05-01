#pragma once
#include "common.h"

class t_window
{
public:
	void create(const char* title);
	void close();
	bool is_open();
	void toggle_fullscreen();
	void clear(rgb color);
	void update();
	int get_random_int(int min, int max);
	rgb pack_rgb(int r, int g, int b);
	rgb get_random_color();
	void draw_tile(const char* bits, int x, int y, rgb color1, rgb color0, bool grid);
	void draw_text(const char* text, int x, int y, rgb color1, rgb color0, bool grid);
	void draw_test_frame_colors();
	void draw_test_frame_pixels();
	void draw_test_frame_tiles();

private:
	static constexpr int TILE_W = 8;
	static constexpr int TILE_H = 8;
	static constexpr int TILESIZE = TILE_W * TILE_H;
	static constexpr int SCR_W = 360;
	static constexpr int SCR_H = 200;
	static constexpr int BUFLEN = SCR_W * SCR_H * sizeof(rgb);
	static constexpr int SCR_COLS = SCR_W / TILE_W;
	static constexpr int SCR_ROWS = SCR_H / TILE_H;
	static constexpr int WND_ZOOM = 3;
	static constexpr int WND_W = SCR_W * WND_ZOOM;
	static constexpr int WND_H = SCR_H * WND_ZOOM;

	SDL_Window* wnd = NULL;
	SDL_Renderer* rend = NULL;
	SDL_Texture* tex = NULL;
	rgb scrbuf[BUFLEN] = { 0 };
	bool fullscreen = false;
};
