#pragma once
#include "common.h"
#include "t_program_line.h"
#include "t_source_line.h"

struct t_program {
	std::vector<t_source_line> src_lines;
	std::vector<t_program_line> lines;
	std::map<string, int> labels;
	std::vector<string> data;
	t_program();
	void clear();
	bool load_plain(string path);
};
