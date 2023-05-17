#include "ptm_graphics_base.h"
#include "ptm_core.h"

t_ptm_screen scr;

void ptm_init_window(int buf_w, int buf_h, int size, rgb bgcol)
{
	scr.initialized = true;
	scr.buf_w = buf_w;
	scr.buf_h = buf_h;
	scr.buf_len = buf_w * buf_h;
	scr.wnd_size = size;
	scr.bgcol = bgcol;

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	scr.pixel_buf = new rgb[scr.buf_len];
	scr.wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		scr.wnd_size * scr.buf_w, scr.wnd_size * scr.buf_h, 0);
	scr.rend = SDL_CreateRenderer(scr.wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetLogicalSize(scr.rend, scr.buf_w, scr.buf_h);
	scr.tx = SDL_CreateTexture(scr.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, scr.buf_w, scr.buf_h);
	SDL_SetTextureBlendMode(scr.tx, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawBlendMode(scr.rend, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(scr.rend, 0, 0, 0, 255);
	SDL_RenderClear(scr.rend);
	SDL_RenderPresent(scr.rend);
	ptm_clear_screen();
	ptm_update();
	SDL_SetWindowPosition(scr.wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_RaiseWindow(scr.wnd);
}
void ptm_free_window()
{
	delete scr.pixel_buf;           scr.pixel_buf = nullptr;
	SDL_DestroyTexture(scr.tx);     scr.tx = nullptr;
	SDL_DestroyRenderer(scr.rend);  scr.rend = nullptr;
	SDL_DestroyWindow(scr.wnd);     scr.wnd = nullptr;
}
void ptm_refresh_window()
{
	if (!scr.initialized)
		return;

	static int pitch;
	static void* pixels;

	SDL_LockTexture(scr.tx, NULL, &pixels, &pitch);
	SDL_memcpy(pixels, scr.pixel_buf, scr.buf_len * sizeof(rgb));
	SDL_UnlockTexture(scr.tx);
	SDL_RenderClear(scr.rend);
	SDL_RenderCopy(scr.rend, scr.tx, NULL, NULL);
	SDL_RenderPresent(scr.rend);

	scr.frame_counter++;
}
void ptm_toggle_fullscreen()
{
	Uint32 flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	Uint32 is_full = SDL_GetWindowFlags(scr.wnd) & flag;
	SDL_SetWindowFullscreen(scr.wnd, is_full ? 0 : flag);
	ptm_update();
}
void ptm_set_window_title(string title)
{
	SDL_SetWindowTitle(scr.wnd, title.c_str());
}
void ptm_set_window_bgcol(rgb bgcol)
{
	scr.bgcol = bgcol;
}
void ptm_clear_screen()
{
	SDL_memset4(scr.pixel_buf, scr.bgcol, scr.buf_len);
}
void ptm_pset(int x, int y, rgb color)
{
	if (x >= 0 && y >= 0 && x < scr.buf_w && y < scr.buf_h) {
		scr.pixel_buf[y * scr.buf_w + x] = color;
	}
}
void ptm_draw_tile_bin(binary str, int x, int y, rgb fgc, rgb bgc, bool transparent)
{
	const int px = x;
	for (auto& ch : str) {
		if (transparent) {
			if (ch == '1') {
				ptm_pset(x, y, fgc);
			}
		}
		else {
			ptm_pset(x, y, ch == '1' ? fgc : bgc);
		}
		x++;
		if (x >= px + 8) {
			x = px;
			y++;
		}
	}
}
void ptm_draw_tile_rgb(rgb colors[64], int x, int y, rgb transparency_key)
{
	const int px = x;
	for (int i = 0; i < 64; i++) {
		rgb& color = colors[i];
		if (color != transparency_key) {
			ptm_pset(x, y, color);
		}
		x++;
		if (x >= px + 8) {
			x = px;
			y++;
		}
	}
}
