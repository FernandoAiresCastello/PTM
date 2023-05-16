#include "ptm_commands.h"
#include "ptm_core.h"
#include "ptm_graphics.h"

#define CMD(x) ptm_commands[x] = [](t_params& arg)
#define STR(x) intp->require_string(arg[x]);
#define NUM(x) intp->require_number(arg[x]);
#define LBL(x) intp->require_label(arg[x]);

unordered_map<string, function<void(t_params&)>> ptm_commands;

void ptm_init_commands()
{
	// Compile-time commands
	
	CMD("INCL") {};
	CMD("DATA") {};
	CMD("WINDOW") {};

	// Run-time commands

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
		string title = STR(0);
		ptm_set_window_title(title);
	};
	CMD("CLS") {
		ARGC(0);
		ptm_clear_screen();
	};
	CMD("WCOL") {
		ARGC(1);
		rgb bgcol = NUM(0);
		ptm_set_window_bgcol(bgcol);
	};
	CMD("DBG.BRK") {
		ARGC(0);
		debugger;
	};
	CMD("DBG.MSG") {
		ARGC(1);
		string msg = STR(0);
		ptm_show_message_box(msg);
	};
	CMD("PAUSE") {
		ARGC(1);
		int frames = NUM(0);
		for (int i = 0; i <= frames; i++) {
			ptm_idle_frame();
		}
	};
	CMD("GOTO") {
		ARGC(1);
		string label = LBL(0);
		if (!label.empty()) {
			intp->goto_label(label);
		}
	};
	CMD("CALL") {
		ARGC(1);
		string label = LBL(0);
		if (!label.empty()) {
			intp->call_label(label);
		}
	};
	CMD("RET") {
		ARGC(0);
		intp->return_from_call();
	};
}
