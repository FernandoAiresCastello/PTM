#include "ptm_graphics_base.h"
#include "ptm_core.h"
#include "ptm_tile_system.h"
#include "ptm_sprites.h"
#include "ptm_color_palette.h"

t_screen scr;

void ptm_init_window(int buf_w, int buf_h, int size, rgb bgcol, int default_buf_layer_count)
{
	scr.initialized = true;
	scr.buf_w = buf_w;
	scr.buf_h = buf_h;
	scr.buf_len = buf_w * buf_h;
	scr.wnd_size = size;
	scr.bgcol = bgcol;
	scr.cols = buf_w / PTM_TILE_SIZE;
	scr.rows = buf_h / PTM_TILE_SIZE;

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

	ptm_set_tile_animation_speed(80);
	ptm_create_default_tilebuffer(default_buf_layer_count);
	ptm_clear_screen();
	ptm_update();
	ptm_enable_mouse_pointer(false);

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

	ptm_draw_visible_buffers();
	sprites.draw_all_visible_with_no_buffer();
	ptm_update_tile_animation();

	static int pitch;
	static void* pixels;

	SDL_LockTexture(scr.tx, NULL, &pixels, &pitch);
	SDL_memcpy(pixels, scr.pixel_buf, scr.buf_len * sizeof(rgb));
	SDL_UnlockTexture(scr.tx);
	int r = ptm_rgb_extract_r(scr.bgcol);
	int g = ptm_rgb_extract_g(scr.bgcol);
	int b = ptm_rgb_extract_b(scr.bgcol);
	SDL_SetRenderDrawColor(scr.rend, r, g, b, 255);
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
void ptm_enable_mouse_pointer(bool enable)
{
	SDL_ShowCursor(enable);
}
int ptm_mouse_get_x()
{
	int x = 0;
	SDL_GetMouseState(&x, nullptr);
	return x / scr.wnd_size;
}
int ptm_mouse_get_y()
{
	int y = 0;
	SDL_GetMouseState(nullptr, &y);
	return y / scr.wnd_size;
}
bool ptm_mouse_get_btn_left()
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK;
}
bool ptm_mouse_get_btn_right()
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK;
}
bool ptm_mouse_get_btn_middle()
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MMASK;
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
void ptm_clip(t_clip& clip)
{
	scr.clip = clip;
	scr.clip.enabled = true;
}
void ptm_clip(int x1, int y1, int x2, int y2, int x_off, int y_off)
{
	scr.clip.enabled = true;
	scr.clip.x1 = x1;
	scr.clip.y1 = y1;
	scr.clip.x2 = x2;
	scr.clip.y2 = y2;
	scr.clip.x_offset = x_off;
	scr.clip.y_offset = y_off;
}
void ptm_clip(int x1, int y1, int x2, int y2)
{
	scr.clip.enabled = true;
	scr.clip.x1 = x1;
	scr.clip.y1 = y1;
	scr.clip.x2 = x2;
	scr.clip.y2 = y2;
}
void ptm_clip_scroll(int dx, int dy)
{
	scr.clip.x_offset -= dx;
	scr.clip.y_offset -= dy;
}
void ptm_fill_clip(rgb color)
{
	for (int y = scr.clip.y1; y <= scr.clip.y2; y++) {
		for (int x = scr.clip.x1; x <= scr.clip.x2; x++) {
			if (x >= 0 && y >= 0 && x < scr.buf_w && y < scr.buf_h) {
				scr.pixel_buf[y * scr.buf_w + x] = color;
			}
		}
	}
}
void ptm_unclip()
{
	scr.clip.enabled = false;
	scr.clip.x1 = 0;
	scr.clip.y1 = 0;
	scr.clip.x2 = 0;
	scr.clip.y2 = 0;
	scr.clip.x_offset = 0;
	scr.clip.y_offset = 0;
}
void ptm_pset(int x, int y, rgb color)
{
	if (scr.clip.enabled) {
		x += scr.clip.x1 + scr.clip.x_offset;
		y += scr.clip.y1 + scr.clip.y_offset;
		if (x >= 0 && y >= 0 && x >= scr.clip.x1 && y >= scr.clip.y1 &&
			x < scr.buf_w && y < scr.buf_h && x <= scr.clip.x2 && y <= scr.clip.y2) {
			scr.pixel_buf[y * scr.buf_w + x] = color;
		}
	}
	else {
		if (x >= 0 && y >= 0 && x < scr.buf_w && y < scr.buf_h) {
			scr.pixel_buf[y * scr.buf_w + x] = color;
		}
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
		if (x >= px + PTM_TILE_SIZE) {
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
		if (x >= px + PTM_TILE_SIZE) {
			x = px;
			y++;
		}
	}
}
void ptm_save_screenshot(string file)
{
	ptm_refresh_window();
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, scr.buf_w, scr.buf_h, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_memcpy(surface->pixels, scr.pixel_buf, scr.buf_len * sizeof(rgb));
	SDL_SaveBMP(surface, file.c_str());
	SDL_FreeSurface(surface);
}
