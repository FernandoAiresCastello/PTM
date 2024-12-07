#include "t_system.h"
#include "t_ptm.h"
#include "t_main_window.h"
#include "t_screen.h"
#include "t_charset.h"
#include "t_image.h"
#include "t_color.h"
#include "t_subsystem.h"

t_system::t_system()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

t_system::~t_system()
{
    for (int i = 0; i < subsystems.size(); i++) {
        delete subsystems[i];
        subsystems[i] = nullptr;
    }
    subsystems.clear();

    quit();
	SDL_Quit();
}

void t_system::quit()
{
    ptm.wnd.close();
}

int t_system::run()
{
    ptm.wnd.open("PTM", 360, 200, 4, 4);
    ptm.scr.set_backcolor(0x108020);

    while (ptm.wnd.is_open()) {

        ptm.scr.clear();
        on_draw();
        ptm.scr.update();

        SDL_Event event;
        SDL_PollEvent(&event);

        if (event.type == SDL_EVENT_QUIT)
            quit();
        else if (event.type == SDL_EVENT_KEY_DOWN)
            on_keydown(event.key.key, event.key.mod);
    }

    return 0;
}

void t_system::on_draw()
{
    for (auto& sys : subsystems) {
        if (sys->is_active()) {
            sys->on_draw();
        }
    }
}

void t_system::on_keydown(t_keycode& key, t_keymod& mod)
{
    if (key == SDLK_RETURN && ptm.kb.alt()) {
        ptm.scr.toggle_fullscreen();
    }
    else {
        for (auto& sys : subsystems) {
            if (sys->is_active()) {
                sys->on_keydown(key, mod);
            }
        }
    }
}
