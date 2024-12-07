#include "PTM.h"

PTM::PTM()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    scr.wnd = &wnd;
}

PTM::~PTM()
{
	SDL_Quit();
}

int PTM::run()
{
	wnd.create("PTM", 360, 200, 4, 4, 0x000000);

    SDL_Event event;

    while (true) {

        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            break;

        wnd.update();
    }

    return 0;
}
