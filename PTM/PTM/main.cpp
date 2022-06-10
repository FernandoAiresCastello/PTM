#include "common.h"
#include "t_program_editor.h"

int main(int argc, char* argv[]) {
	TBufferedWindow* wnd = new TBufferedWindow(2, 32, 24, 3, 3);
	wnd->SetTitle("PTM");
	wnd->Show();
	t_program_editor* editor = new t_program_editor(wnd);
	editor->print_intro();

	bool running = true;
	while (running) {
		if (editor->exit_requested) {
			running = false;
			break;
		}
		editor->print_debug();
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		bool handled = false;
		if (e.type == SDL_QUIT) {
			handled = true;
			running = false;
			break;
		} else if (e.type == SDL_KEYDOWN) {
			auto key = e.key.keysym.sym;
			if (key == SDLK_RETURN && TKey::Alt()) {
				handled = true;
				wnd->ToggleFullscreen();
			} else if (key == SDLK_ESCAPE) {
				handled = true;
				running = false;
				break;
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
