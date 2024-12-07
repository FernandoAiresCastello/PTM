#include "PTM.h"
#include "t_image.h"

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
	wnd.open("PTM", 360, 200, 4, 4, 0x108020);

    t_image img;
    img.load("player.bmp");
    img.set_transparency_key(0xffffff);

    while (wnd.is_open()) {

        scr.draw_image(&img, 0, 0);
        scr.update();

        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            quit();
        else if (event.type == SDL_EVENT_KEY_DOWN)
            on_keydown(event.key.key);
    }

    return 0;
}

void PTM::quit()
{
    wnd.close();
}

void PTM::on_keydown(SDL_Keycode& key)
{
    if (key == SDLK_ESCAPE)
        quit();
}
