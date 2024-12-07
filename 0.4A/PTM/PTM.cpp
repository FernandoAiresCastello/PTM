#include "PTM.h"
#include "t_image.h"
#include "t_color.h"

PTM::PTM()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    scr.wnd = &wnd;
    scr.charset = &charset;
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

        scr.draw_image(&img, 100, 50);
        scr.putch('A', 10, 10, 0xff0000, 0x00ffff);
        scr.putch('B', 11, 11, 0xffff00);
        scr.print("Hello World 1!", 0, 0, 0xff00ff, 0x0000ff);
        scr.print("Hello World 2!", 1, 1, 0x00ffff);
        scr.update();

        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            quit();
        else if (event.type == SDL_EVENT_KEY_DOWN)
            on_keydown(event.key.key, event.key.mod);
    }

    return 0;
}

void PTM::quit()
{
    wnd.close();
}

void PTM::on_keydown(SDL_Keycode& key, SDL_Keymod& mod)
{
    if (key == SDLK_ESCAPE)
        quit();
    else if (key == SDLK_RETURN && (SDL_GetModState() & SDL_KMOD_ALT))
        scr.toggle_fullscreen();
}
