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
    int buf_len;
    int* buf;
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
    graphics.buf_len = 0;
    graphics.buf = NULL;
}
void ptm_exit() {
    free(graphics.buf);
    if (graphics.tex) SDL_DestroyTexture(graphics.tex);
    if (graphics.rend) SDL_DestroyRenderer(graphics.rend);
    if (graphics.wnd) SDL_DestroyWindow(graphics.wnd);
    SDL_Quit();
    exit(0);
}
void ptm_halt() {
    SDL_Event event;
    while (1) {
        ptm_update_window();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                ptm_exit();
            }
        }
        SDL_Delay(1);
    }
}
void ptm_open_window(int wnd_w, int wnd_h, int buf_w, int buf_h) {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    graphics.wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wnd_w, wnd_h, 0);
    graphics.rend = SDL_CreateRenderer(graphics.wnd, -1, SDL_RENDERER_PRESENTVSYNC || SDL_RENDERER_ACCELERATED || SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderSetLogicalSize(graphics.rend, buf_w, buf_h);
    graphics.tex = SDL_CreateTexture(graphics.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, buf_w, buf_h);
    graphics.buf_w = buf_w;
    graphics.buf_h = buf_h;
    graphics.buf_len = buf_w * buf_h;
    graphics.buf = calloc(graphics.buf_len, sizeof(int));
    ptm_update_window();
    SDL_SetWindowPosition(graphics.wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RaiseWindow(graphics.wnd);
}
void ptm_update_window() {
    static int pitch;
    static void* pixels;
    SDL_LockTexture(graphics.tex, NULL, &pixels, &pitch);
    SDL_memcpy(pixels, graphics.buf, graphics.buf_len * sizeof(int));
    SDL_UnlockTexture(graphics.tex);
    SDL_RenderCopy(graphics.rend, graphics.tex, NULL, NULL);
    SDL_RenderPresent(graphics.rend);
}
void ptm_put_pixel_linear(int i, int rgb) {
    if (i >= 0 && i < graphics.buf_len) {
        graphics.buf[i] = rgb;
    }
}
void ptm_put_pixel(int x, int y, int rgb) {
    if (x >= 0 && y >= 0 && x < graphics.buf_w && y < graphics.buf_h) {
        graphics.buf[y * graphics.buf_w + x] = rgb;
    }
}
void ptm_clear_window(int rgb) {
    for (int i = 0; i < graphics.buf_len; i++) {
        graphics.buf[i] = rgb;
    }
}
void ptm_msgbox(const char* msg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "", msg, NULL);
}
