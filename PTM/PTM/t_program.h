#pragma once
#include "common.h"
#include "t_program_line.h"
#include "t_source_line.h"

struct t_program {
	std::vector<t_source_line> src_lines;
	std::vector<t_program_line> lines;
	t_program();
	void add_src_line(int number, string src);
	t_source_line* get_src_line(int number);
	std::vector<string> get_src_lines();
	bool delete_line(int number);
	bool has_line_number(int number);
	void sort();
	void renumerate(int increment);
};
