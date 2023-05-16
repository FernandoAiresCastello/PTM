#pragma once
#include "../Common/common.h"

struct t_ptm_screen {
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
};

extern t_ptm_screen scr;

void ptm_init_window(int buf_w, int buf_h, int size, rgb bgcol);
void ptm_free_window();
void ptm_refresh_window();
void ptm_toggle_fullscreen();
void ptm_set_window_title(string title);
void ptm_set_window_bgcol(rgb bgcol);
void ptm_clear_screen();
void ptm_pset(int x, int y, rgb color);
