#pragma once
#include "common.h"
#include "t_param.h"

struct t_program_line {
	string src;
	int src_line_nr = 0;
	string cmd;
	t_params params;
	t_program_line();
};
