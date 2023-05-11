#include "api_private.h"

#define BUF_W       256
#define BUF_H       192
#define WND_SIZE    4

struct {
    SDL_Window* wnd;
    SDL_Renderer* rend;
    SDL_Texture* tx;
    rgb* buf;
    int buf_len;
    int buf_w;
    int buf_h;
    rgb back_color;
    int pixel_w;
    int pixel_h;
} screen;

void init_screen()
{
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    screen.wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WND_SIZE * BUF_W, WND_SIZE * BUF_H, 0);
    screen.rend = SDL_CreateRenderer(screen.wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderSetLogicalSize(screen.rend, BUF_W, BUF_H);
    screen.tx = SDL_CreateTexture(screen.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BUF_W, BUF_H);
    SDL_SetTextureBlendMode(screen.tx, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawBlendMode(screen.rend, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(screen.rend, 0, 0, 0, 255);
    SDL_RenderClear(screen.rend);
    SDL_RenderPresent(screen.rend);
    SDL_SetWindowPosition(screen.wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RaiseWindow(screen.wnd);
}
void free_screen()
{
    free(screen.buf);                   screen.buf = NULL;
    SDL_DestroyTexture(screen.tx);      screen.tx = NULL;
    SDL_DestroyRenderer(screen.rend);   screen.rend = NULL;
    SDL_DestroyWindow(screen.wnd);      screen.wnd = NULL;
    
}
