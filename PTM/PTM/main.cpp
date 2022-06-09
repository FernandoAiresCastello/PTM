#include "common.h"
#include "t_program_editor.h"

int main(int argc, char* argv[]) {
	TBufferedWindow* wnd = new TBufferedWindow(2, 32, 24, 3, 3);
	wnd->Show();
	t_program_editor* editor = new t_program_editor(wnd);
	editor->print_intro();

	while (true) {
		editor->draw();
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		bool handled = false;
		if (e.type == SDL_QUIT) {
			handled = true;
			break;
		} else if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN && TKey::Alt()) {
				handled = true;
				wnd->ToggleFullscreen();
			}
			if (!handled) {
				editor->on_keydown(key, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
			}
		}
	}

	delete editor;
	delete wnd;
	return 0;
}
