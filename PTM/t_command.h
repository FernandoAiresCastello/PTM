#pragma once
#include "common.h"
#include "t_param.h"

struct t_interpreter;
struct t_environment;

struct t_command {
	t_command(t_interpreter* intp);
	void halt(t_params& arg);
	void exit(t_params& arg);
private:
	t_interpreter* intp;
	t_environment* env;
	void argc(t_params& arg, int expected);
	void argc(t_params& arg, int min, int max);
};
