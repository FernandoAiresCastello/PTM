#pragma once
#include <SDL.h>
#include "t_color.h"
#include "t_string.h"
#include "t_binary.h"
#include "t_charset.h"

class t_window
{
public:
	void create(const char* title);
	void close();
	bool is_open();
	void toggle_fullscreen();
	void clear(t_color color);
	void update();
	int width() const;
	int height() const;
	int cols() const;
	int rows() const;
	void draw_pixel(int x, int y, t_color color);
	void draw_pixels(t_binary pixels, int x, int y, t_color color1, t_color color0, bool grid);
	void draw_char(t_charset* charset, int char_index, int x, int y, t_color color1, t_color color0, bool grid);
	void draw_text(t_charset* charset, t_string text, int x, int y, t_color color1, t_color color0, bool grid);

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
