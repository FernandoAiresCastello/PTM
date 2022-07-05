#include "common.h"
#include "t_config.h"
#include "t_program_editor.h"
#include "t_globals.h"
#include "t_machine.h"

int main(int argc, char* argv[]) {
	t_globals g;
	g.cfg->load();
	g.snd->SetVolume(TSound::MinVolume + 1000);
	g.wnd = new TBufferedWindow(2, 32, 24, 3, 3);
	g.wnd->SetTitle("PTM");
	g.wnd->Show();

	t_program_editor* editor = new t_program_editor(&g);
	editor->run();

	delete editor;
	return 0;
}
