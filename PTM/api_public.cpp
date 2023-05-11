#include "api_public.h"
#include "api_private.h"

void ptm_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	init_screen();
}
void ptm_exit()
{
	free_screen();
	SDL_Quit();
    exit(0);
}
void ptm_halt()
{
    while (true) {
        SDL_Event e = { 0 };
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            ptm_exit();
            break;
        }
        else if (e.type == SDL_KEYDOWN) {
            const SDL_Keycode key = e.key.keysym.sym;
            if (key == SDLK_ESCAPE) {
                ptm_exit();
                break;
            }
            else if (key == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
                // toggle fullscreen
            }
        }
    }
}
