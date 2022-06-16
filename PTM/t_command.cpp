#include "t_command.h"
#include "t_interpreter.h"
#include "t_game.h"

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	game = intp->game;
}
void t_command::argc(t_params& arg, int expected) {
	if (arg.size() != expected) {
		intp->abort("Invalid argument count");
	}
}
void t_command::argc(t_params& arg, int min, int max) {
	if (arg.size() < min || arg.size() > max) {
		intp->abort("Invalid argument count");
	}
}
void t_command::halt(t_params& arg) {
	argc(arg, 0);
	intp->halted = true;
}
void t_command::exit(t_params& arg) {
	argc(arg, 0);
	intp->running = false;
}
