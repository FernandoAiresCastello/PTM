#pragma once
#include "common.h"
#include "t_param.h"

struct t_source_line;

struct t_program_line {
	t_source_line* src;
	string cmd;
	std::vector<t_param> params;
	bool ignore;
	t_program_line();
};
