#pragma once
#include "common.h"
#include "t_param.h"

struct t_interpreter;
struct t_machine;

struct t_command {
	t_command(t_interpreter* intp);
	bool execute(string& cmd, t_params& args);
private:
	t_interpreter* intp;
	t_machine* machine;
	void halt(t_params& arg);
	void exit(t_params& arg);
	void branch(t_params& arg);
};
