#include <SDL.h>
#include "t_window.h"
#include "t_util.h"

#define sdl_wnd ((SDL_Window*)wnd)
#define sdl_rend ((SDL_Renderer*)rend)
#define sdl_tex ((SDL_Texture*)tex)

void t_window::open(const t_string& title, int size)
{
	if (size < 1) size = 1;
	else if (size > 5) size = 5;

	int wnd_w = image_w * size;
	int wnd_h = image_h * size;

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	auto wnd_flags = (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) | SDL_WINDOW_HIDDEN;

	wnd = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wnd_w, wnd_h, wnd_flags);
	rend = SDL_CreateRenderer(sdl_wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	tex = SDL_CreateTexture(sdl_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, image_w, image_h);

	SDL_SetRenderDrawBlendMode(sdl_rend, SDL_BLENDMODE_NONE);
	SDL_SetTextureBlendMode(sdl_tex, SDL_BLENDMODE_NONE);
	SDL_RenderSetLogicalSize(sdl_rend, image_w, image_h);
	SDL_SetWindowPosition(sdl_wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	clear(0x000000);
	update();

	SDL_ShowWindow(sdl_wnd);
	SDL_RaiseWindow(sdl_wnd);
}

void t_window::close()
{
	if (!is_open())
		return;

	SDL_DestroyTexture(sdl_tex);
	SDL_DestroyRenderer(sdl_rend);
	SDL_DestroyWindow(sdl_wnd);

	tex = nullptr;
	rend = nullptr;
	wnd = nullptr;
}

bool t_window::is_open()
{
	return wnd != nullptr;
}

void t_window::toggle_fullscreen()
{
	Uint32 flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	Uint32 is_full = SDL_GetWindowFlags(sdl_wnd) & flag;
	SDL_SetWindowFullscreen(sdl_wnd, is_full ? 0 : flag);
	update();
}

void t_window::clear(const t_color& color)
{
	for (int i = 0; i < buflen; i++) {
		scrbuf[i] = color.to_rgb();
	}
}

void t_window::update()
{
	tile_anim.update();

	static int pitch;
	static void* pixels;

	SDL_LockTexture(sdl_tex, nullptr, &pixels, &pitch);
	SDL_memcpy(pixels, scrbuf, buflen);
	SDL_UnlockTexture(sdl_tex);
	SDL_RenderCopy(sdl_rend, sdl_tex, nullptr, nullptr);
	SDL_RenderPresent(sdl_rend);

	frame_counter++;
}

void t_window::reset_frame_counter()
{
	frame_counter = 0;
}

uint32_t t_window::get_frame_count() const
{
	return frame_counter;
}

int t_window::get_animation_frame() const
{
	return tile_anim.frame;
}

#define is_valid_pixel(x, y)		x >= 0 && y >= 0 && x < image_w && y < image_h
#define set_pixel(x, y, color)		if (is_valid_pixel(x, y)) { scrbuf[y * image_w + x] = color.to_rgb(); }
#define snap_to_grid(grid, x, y)	if (grid) { x *= t_tile::width; y *= t_tile::height; }

void t_window::draw_pixel(int x, int y, const t_color& color)
{
	set_pixel(x, y, color);
}

void t_window::draw_pixels(const t_binary& pixels, int x, int y, const t_color& color1, const t_color& color0, bool grid)
{
	snap_to_grid(grid, x, y);

	int px = x;
	int py = y;
	const int MAX_X = x + t_tile::width;

	for (int i = 0; i < tilesize; i++) {
		set_pixel(px, py, (pixels[i] == '1' ? color1 : color0));
		if (++px >= MAX_X) {
			px = x;
			py++;
		}
	}
}

void t_window::draw_char(t_charset* charset, int char_index, int x, int y, const t_color& color1, const t_color& color0, bool grid)
{
	snap_to_grid(grid, x, y);

	draw_pixels(charset->get(char_index), x, y, color1, color0, false);
}

void t_window::draw_text(t_charset* charset, const t_string& text, int x, int y, const t_color& color1, const t_color& color0, bool grid)
{
	snap_to_grid(grid, x, y);

	const char* ctext = text.c_str();
	for (int i = 0; i < strlen(ctext); i++) {
		draw_pixels(charset->get(ctext[i]), x, y, color1, color0, false);
		x += t_tile::width;
	}
}
