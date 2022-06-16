#pragma once
#include "common.h"

struct t_program;
struct t_program_line;

struct t_compiler {
	std::vector<string> errors;
	void run(t_program* prg);
private:
	bool compile(t_program* prg, t_program_line* new_line, string src_line, int src_line_nr);
	void add_error(int src_line_nr, string src, string msg);
};
