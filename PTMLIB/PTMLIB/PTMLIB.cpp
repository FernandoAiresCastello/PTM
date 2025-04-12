#include "PTMLIB.h"

static constexpr int image_w = 360;
static constexpr int image_h = 200;
static constexpr int buflen = image_w * image_h * sizeof(PTMLIB::t_rgb);

SDL_Window* wnd = nullptr;
SDL_Renderer* rend = nullptr;
SDL_Texture* tex = nullptr;
bool fullscreen = false;
PTMLIB::t_rgb scrbuf[buflen] = { 0 };

void PTMLIB::ptm_init(int size)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	if (size < 1) size = 1;
	else if (size > 5) size = 5;

	int wnd_w = image_w * size;
	int wnd_h = image_h * size;

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	auto wnd_flags = (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) | SDL_WINDOW_HIDDEN;

	wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wnd_w, wnd_h, wnd_flags);
	rend = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, image_w, image_h);

	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
	SDL_RenderSetLogicalSize(rend, image_w, image_h);
	SDL_SetWindowPosition(wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	ptm_clear_window(0x000000);
	ptm_update_window();

	SDL_ShowCursor(false);
	SDL_ShowWindow(wnd);
	SDL_RaiseWindow(wnd);
}

void PTMLIB::ptm_destroy()
{
	SDL_Quit();
}

void PTMLIB::ptm_clear_window(t_rgb color)
{
	for (int i = 0; i < buflen; i++)
		scrbuf[i] = color;
}

void PTMLIB::ptm_update_window()
{
	static int pitch;
	static void* pixels;

	SDL_LockTexture(tex, nullptr, &pixels, &pitch);
	SDL_memcpy(pixels, scrbuf, buflen);
	SDL_UnlockTexture(tex);
	SDL_RenderCopy(rend, tex, nullptr, nullptr);
	SDL_RenderPresent(rend);
}
