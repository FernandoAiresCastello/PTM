#include "common.h"
#include "t_config.h"
#include "t_program_editor.h"

int main(int argc, char* argv[]) {
	t_config cfg;
	cfg.load();
	TSound snd;
	snd.SetVolume(TSound::MinVolume + 1000);
	TBufferedWindow* wnd = new TBufferedWindow(2, cfg.cols, cfg.rows, cfg.pixel_w, cfg.pixel_h);
	wnd->SetTitle("PTM");
	wnd->Show();
	t_program_editor* editor = new t_program_editor(wnd, &cfg, &snd);
	editor->run();

	delete editor;
	delete wnd;
	return 0;
}
