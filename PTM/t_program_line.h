#pragma once
#include "common.h"
#include "t_param.h"

struct t_program_line {
	string src;
	int src_line_nr = 0;
	string cmd;
	t_params params;
	bool is_endif = false;
	t_program_line();
};
