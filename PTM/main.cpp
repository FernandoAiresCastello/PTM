#include "common.h"
#include "t_config.h"
#include "t_program_editor.h"

int main(int argc, char* argv[]) {
	t_config cfg;
	cfg.load();

	TBufferedWindow* wnd = new TBufferedWindow(2, cfg.cols, cfg.rows, cfg.pixel_w, cfg.pixel_h);
	wnd->SetTitle("PTM");
	wnd->Show();

	TSound snd;
	snd.SetVolume(TSound::MinVolume + 1000);

	t_program_editor* editor = new t_program_editor(wnd, &snd, &cfg);

	bool running = true;
	while (running) {
		if (editor->exit_requested) {
			running = false;
			break;
		}
		editor->print_borders();
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
