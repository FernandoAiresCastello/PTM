#include "ptm_commands.h"
#include "ptm_core.h"

#define CMD(x) cmap[x] = [](t_params& arg)
unordered_map<string, function<void(t_params&)>> cmap;

void ptm_init_commands()
{
	CMD("NOP") {
		// No operation
	};
	CMD("EXIT") {
		ptm_exit();
	};
	CMD("HALT") {
		ptm_halt();
	};
	CMD("WINDOW") {
		
	};
}
