#pragma once
#include "../common.h"
#include "t_param.h"

struct t_program_line {
	string file;
	string src;
	int src_line_nr = 0;
	string cmd;
	t_params params;
	bool is_if = false;
	bool is_endif = false;
	bool is_endfor = false;
};
