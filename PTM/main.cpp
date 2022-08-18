#include <TWindowCreationFlags.h>
#include "common.h"
#include "t_config.h"
#include "t_program_editor.h"
#include "t_globals.h"
#include "t_machine.h"
#include "t_layer.h"
#include "t_compiler.h"
#include "t_interpreter.h"

int main(int argc, char* argv[]) {
	t_globals g;
	g.snd->SetVolume(TSound::MinVolume + 1000);
	TWindowCreationFlags::RenderScaleQuality = "best";
	g.wnd = new TBufferedWindow(t_layer::max, 45, 25, 3, 3);
	g.wnd->Show();

	if (!File::Exists(PTM_MAIN_PROG_FILE)) {
		MsgBox::Error("PTM", "Main program file " PTM_MAIN_PROG_FILE " not found");
		return 0;
	}

	t_program* prg = new t_program();
	prg->load_plain(PTM_MAIN_PROG_FILE);
	t_compiler compiler;
	compiler.run(prg);
	if (compiler.errors.empty()) {
		t_machine* machine = new t_machine(g.wnd);
		machine->perfmon = g.perfmon;
		machine->snd = g.snd;
		t_interpreter* interpreter = new t_interpreter();
		interpreter->run(prg, machine, g.wnd);
		auto errors = interpreter->errors;
		delete interpreter;
		delete machine;
		if (!errors.empty()) {
			MsgBox::Error("PTM", errors[0]);
		}
	} else {
		MsgBox::Error("PTM", compiler.errors[0]);
	}
	delete prg;
	return 0;
}
