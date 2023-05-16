#include "ptm_commands.h"
#include "ptm_core.h"

#define CMD(x) ptm_commands[x] = [](t_params& arg)
unordered_map<string, function<void(t_params&)>> ptm_commands;

void ptm_init_commands()
{
	// Compile-time commands
	
	CMD("INCL") {};
	CMD("DATA") {};
	CMD("WINDOW") {};

	// Runtime commands

	CMD("NOP") {
		ARGC(0);
		ptm_idle_frame();
	};
	CMD("EXIT") {
		ARGC(0);
		ptm_exit();
	};
	CMD("HALT") {
		ARGC(0);
		ptm_halt();
	};
	CMD("UPDATE") {
		ARGC(0);
		ptm_update();
	};
	CMD("TITLE") {
		ARGC(1);
		string title = intp->require_string(arg[0]);
		ptm_set_window_title(title);
	};
	CMD("CLS") {
		ARGC(0);
		ptm_clear_screen();
	};
	CMD("WCOL") {
		ARGC(1);
		rgb bgcol = intp->require_number(arg[0]);
		ptm_set_window_bgcol(bgcol);
	};
	CMD("DBG.BRK") {
		ARGC(0);
		debugger;
	};
	CMD("DBG.MSG") {
		ARGC(1);
		string msg = intp->require_string(arg[0]);
		ptm_show_message_box(msg);
	};
}
