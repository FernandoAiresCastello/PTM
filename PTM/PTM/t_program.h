#pragma once
#include "common.h"
#include "t_program_line.h"

struct t_program {
	std::vector<t_program_line> lines;
	t_program();
	void add_line(int number, string code);
	bool delete_line(int number);
	bool has_line_number(int number);
};
