#pragma once
#include "common.h"
#include "t_param.h"

struct t_program_line {
	string src;
	string cmd;
	std::vector<t_param> params;
	t_program_line();
};
