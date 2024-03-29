#pragma once
#include "../Common/common.h"
#include "t_program_line.h"
#include "t_source_line.h"

struct t_program {
	string file;
	vector<t_source_line> src_lines;
	vector<t_program_line> lines;
	unordered_map<string, int> labels;
	t_program();
	void clear();
	bool load_plain(string path);
};
