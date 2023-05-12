#pragma once
#include "../common.h"
#include "t_program_line.h"
#include "t_source_line.h"

struct t_program {
	vector<t_source_line> src_lines;
	vector<t_program_line> lines;
	unordered_map<string, int> labels;
	vector<string> data;
	t_program();
	void clear();
	bool load_plain(string path);
};
