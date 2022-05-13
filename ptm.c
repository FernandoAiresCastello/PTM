#include <stdlib.h>
#include "ptm.h"

struct {
    SDL_Window* wnd;
    SDL_Renderer* rend;
    SDL_Texture* tex;
    int wnd_w;
    int wnd_h;
    int buf_w;
    int buf_h;
} graphics;

void ptm_init() {
    SDL_Init(SDL_INIT_EVERYTHING);

    graphics.wnd = NULL;
    graphics.rend = NULL;
    graphics.tex = NULL;
    graphics.wnd_w = 0;
    graphics.wnd_h = 0;
    graphics.buf_w = 0;
    graphics.buf_h = 0;
}
void ptm_exit() {
    if (graphics.tex) SDL_DestroyTexture(graphics.tex);
    if (graphics.rend) SDL_DestroyRenderer(graphics.rend);
    if (graphics.wnd) SDL_DestroyWindow(graphics.wnd);
    SDL_Quit();
    exit(0);
}
void ptm_open_window(int wnd_w, int wnd_h, int buf_w, int buf_h) {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    graphics.wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wnd_w, wnd_h, 0);
    graphics.rend = SDL_CreateRenderer(graphics.wnd, -1, SDL_RENDERER_PRESENTVSYNC || SDL_RENDERER_ACCELERATED || SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderSetLogicalSize(graphics.rend, buf_w, buf_h);
    graphics.tex = SDL_CreateTexture(graphics.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, buf_w, buf_h);
    SDL_SetWindowPosition(graphics.wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RaiseWindow(graphics.wnd);
}
void ptm_halt() {
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                ptm_exit();
            }
        }
        SDL_Delay(1);
    }
}
