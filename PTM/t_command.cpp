#include "t_command.h"
#include "t_interpreter.h"
#include "t_machine.h"
#include "t_program.h"

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	machine = intp->machine;
}
bool t_command::execute(string& cmd, t_params& args) {
	if		(cmd == "HALT")		halt(args);
	else if (cmd == "EXIT")		exit(args);
	else if (cmd == "GOTO")		branch(args);

	else return false;
	return true;
}
void t_command::halt(t_params& arg) {
	intp->argc(arg, 0);
	intp->halted = true;
}
void t_command::exit(t_params& arg) {
	intp->argc(arg, 0);
	intp->running = false;
}
void t_command::branch(t_params& arg) {
	intp->argc(arg, 1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->cur_line_ix = intp->prg->labels[label];
		intp->branched = true;
	}
}
