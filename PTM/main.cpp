#include "common.h"
#include "t_config.h"
#include "t_program_editor.h"
#include "t_board_editor.h"
#include "t_globals.h"

int main(int argc, char* argv[]) {
	t_globals g;
	g.cfg->load();
	g.snd->SetVolume(TSound::MinVolume + 1000);
	g.wnd = new TBufferedWindow(2, g.cfg->cols, g.cfg->rows, g.cfg->pixel_w, g.cfg->pixel_h);
	g.wnd->SetTitle("PTM");
	g.wnd->Show();

	t_program_editor* editor = new t_program_editor(&g);
	editor->run();
	//t_board_editor* editor = new t_board_editor(&g);
	//editor->run();

	delete editor;
	return 0;
}
