#include "ptm.h"

void ptm_init_window(int wnd_w, int wnd_h, int buf_w, int buf_h) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    SDL_Window* window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wnd_w, wnd_h, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_PRESENTVSYNC || SDL_RENDERER_ACCELERATED || SDL_RENDERER_TARGETTEXTURE);

    SDL_RenderSetLogicalSize(renderer, buf_w, buf_h);

    SDL_Texture* screenTexture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, buf_w, buf_h);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RaiseWindow(window);

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
