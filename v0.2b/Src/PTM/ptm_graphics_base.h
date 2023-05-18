#pragma once
#include "../Common/common.h"

struct t_clip {
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int x_offset = 0;
	int y_offset = 0;
	bool enabled = false;
};
struct t_screen {
	bool initialized = false;
	SDL_Window* wnd = nullptr;
	SDL_Renderer* rend = nullptr;
	SDL_Texture* tx = nullptr;
	rgb* pixel_buf = nullptr;
	int buf_w = 0;
	int buf_h = 0;
	int buf_len = 0;
	int wnd_size = 0;
	rgb bgcol = 0;
	int frame_counter = 0;
	t_clip clip;
	int cols = 0;
	int rows = 0;
};
extern t_screen scr;

void ptm_init_window(int buf_w, int buf_h, int size, rgb bgcol, int default_buf_layer_count);
void ptm_free_window();
void ptm_refresh_window();
void ptm_toggle_fullscreen();
void ptm_set_window_title(string title);
void ptm_set_window_bgcol(rgb bgcol);
void ptm_clear_screen();
void ptm_clip(int x1, int y1, int x2, int y2, int x_off, int y_off);
void ptm_clip(int x1, int y1, int x2, int y2);
void ptm_clip_scroll(int dx, int dy);
void ptm_fill_clip(rgb color);
void ptm_unclip();
void ptm_pset(int x, int y, rgb color);
void ptm_draw_tile_bin(binary str, int x, int y, rgb fgc, rgb bgc, bool transparent);
void ptm_draw_tile_rgb(rgb colors[64], int x, int y, rgb transparency_key);
