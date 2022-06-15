#pragma once
#include "common.h"

struct t_program;
struct t_program_line;

struct t_compiler {
	void run(t_program* prg);
private:
	bool compile(t_program* prg, t_program_line* new_line, string src_line);
	bool is_comment(string src);
	bool is_label(string src);
};
