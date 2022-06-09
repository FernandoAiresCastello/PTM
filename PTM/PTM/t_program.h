#pragma once
#include "common.h"
#include "t_program_line.h"

struct t_program {
	std::vector<t_program_line> lines;
	t_program();
	void add_line(int number, string code);
};
