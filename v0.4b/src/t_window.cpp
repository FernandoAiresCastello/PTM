#include "t_window.h"
#include "t_util.h"

#define is_valid_pixel(x, y)		x >= 0 && y >= 0 && x < SCR_W && y < SCR_H
#define set_pixel(x, y, color)		if (is_valid_pixel(x, y)) { scrbuf[y * SCR_W + x] = color.to_rgb(); }

void t_window::create(const char* title)
{
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	fullscreen = false;

	wnd = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WND_W, WND_H, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	rend = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCR_W, SCR_H);

	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
	SDL_RenderSetLogicalSize(rend, SCR_W, SCR_H);
	SDL_SetWindowPosition(wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_RaiseWindow(wnd);

	clear(0x000000);
	update();
}

void t_window::close()
{
	if (!is_open())
		return;

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wnd);

	tex = NULL;
	rend = NULL;
	wnd = NULL;
}

bool t_window::is_open()
{
	return wnd != NULL;
}

void t_window::toggle_fullscreen()
{
	Uint32 flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	Uint32 is_full = SDL_GetWindowFlags(wnd) & flag;
	SDL_SetWindowFullscreen(wnd, is_full ? 0 : flag);
	update();
}

void t_window::clear(t_color color)
{
	for (int i = 0; i < BUFLEN; i++) {
		scrbuf[i] = color.to_rgb();
	}
}

void t_window::update()
{
	static int pitch;
	static void* pixels;

	SDL_LockTexture(tex, NULL, &pixels, &pitch);
	SDL_memcpy(pixels, scrbuf, BUFLEN);
	SDL_UnlockTexture(tex);
	SDL_RenderCopy(rend, tex, NULL, NULL);
	SDL_RenderPresent(rend);
}

constexpr int t_window::cols() const
{
	return SCR_COLS;
}

constexpr int t_window::rows() const
{
	return SCR_ROWS;
}

void t_window::draw_pixels(t_binary pixels, int x, int y, t_color color1, t_color color0, bool grid)
{
	if (grid) {
		x *= TILE_W;
		y *= TILE_H;
	}

	int px = x;
	int py = y;
	const int MAX_X = x + TILE_W;

	for (int i = 0; i < TILESIZE; i++) {
		set_pixel(px, py, (pixels[i] == '1' ? color1 : color0));
		if (++px >= MAX_X) {
			px = x;
			py++;
		}
	}
}

void t_window::draw_char(t_charset* charset, int char_index, int x, int y, t_color color1, t_color color0, bool grid)
{
	if (grid) {
		x *= TILE_W;
		y *= TILE_H;
	}

	draw_pixels(charset->get(char_index), x, y, color1, color0, false);
}

void t_window::draw_text(t_charset* charset, t_string text, int x, int y, t_color color1, t_color color0, bool grid)
{
	if (grid) {
		x *= TILE_W;
		y *= TILE_H;
	}

	const char* ctext = text.c_str();
	for (int i = 0; i < strlen(ctext); i++) {
		draw_pixels(charset->get(ctext[i]), x, y, color1, color0, false);
		x += TILE_W;
	}
}

void t_window::draw_test_frame_colors()
{
	clear(t_color::get_random());
}

void t_window::draw_test_frame_pixels()
{
	for (int y = 0; y < SCR_H; y++) {
		for (int x = 0; x < SCR_W; x++) {
			set_pixel(x, y, t_color::get_random());
		}
	}
}

void t_window::draw_test_frame_chars(t_charset* charset)
{
	for (int y = 0; y < SCR_ROWS; y++) {
		for (int x = 0; x < SCR_COLS; x++) {
			draw_char(charset, t_util::rnd(0, 255), 
				x, y, t_color::get_random(), t_color::get_random(), true);
		}
	}
}
