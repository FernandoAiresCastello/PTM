#include "common.h"
#include "t_globals.h"
#include "t_program.h"
#include "t_machine.h"
#include "t_compiler.h"
#include "t_interpreter.h"

int main(int argc, char* argv[]) {
	t_globals g;
	g.snd->SetVolume(TSound::MinVolume + 1000);
	TWindowCreationFlags::RenderScaleQuality = "best";

	string prg_file = argc > 1 ? argv[1] : PTM_MAIN_PROG_FILE;
	t_interpreter* interpreter = nullptr;

	do {
		if (!File::Exists(prg_file)) {
			MsgBox::Error("PTM", "Program file \"" + prg_file + "\" not found");
			return 0;
		}
		t_program* prg = new t_program();
		bool load_ok = prg->load_plain(prg_file);
		if (load_ok) {
			t_compiler compiler;
			compiler.run(prg);
			if (compiler.errors.empty()) {
				if (!g.wnd) {
					if (compiler.has_window_def) {
						auto& def = compiler.window_def;
						g.wnd = new TBufferedWindow(def.layers, def.cols, def.rows, def.pixel_w, def.pixel_h);
					} else {
						g.wnd = new TBufferedWindow(3, 45, 25, 3, 3);
					}
					g.wnd->Show();
				}
				t_machine* machine = new t_machine(g.wnd);
				machine->perfmon = g.perfmon;
				machine->snd = g.snd;
				if (interpreter) {
					delete interpreter;
				}
				interpreter = new t_interpreter();
				interpreter->run(prg, machine, g.wnd);
				auto errors = interpreter->errors;
				delete machine;
				if (!errors.empty()) {
					MsgBox::Error("PTM", errors[0]);
				}
			} else {
				MsgBox::Error("PTM", compiler.errors[0]);
			}
		}
		delete prg;

	} while (interpreter && interpreter->reset_requested);

	return 0;
}
