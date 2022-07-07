#pragma once
#include "common.h"
#include "t_program_line.h"

struct t_program {
	std::vector<string> src_lines;
	std::vector<t_program_line> lines;
	std::map<string, int> labels;
	t_program();
	void load(string path);
	void save(string path);
};
