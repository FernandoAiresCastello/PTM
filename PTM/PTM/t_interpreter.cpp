#include "t_interpreter.h"
#include "t_program.h"

t_interpreter::t_interpreter() {
	running = false;
	user_break = false;
	cur_line = 0;
}
bool t_interpreter::has_user_break() {
	return user_break;
}
void t_interpreter::run(t_program* prg, TBufferedWindow* wnd) {
	running = true;
	user_break = false;
	cur_line = 0;
	this->wnd = wnd;
	wnd_buf = wnd->GetBuffer();
	wnd_buf->ClearAllLayers();
	wnd->SetBackColor(0);

	while (running) {
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		wnd->Update();
		if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN && TKey::Alt()) {
				wnd->ToggleFullscreen();
			} else if (key == SDLK_ESCAPE) {
				user_break = true;
				running = false;
				break;
			}
		}
	}
}
