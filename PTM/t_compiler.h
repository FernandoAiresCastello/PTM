#pragma once
#include "common.h"

struct t_program;
struct t_source_line;
struct t_program_line;

struct t_compiler {
	void run(t_program* prg);
private:
	void compile(t_program* prg, t_source_line* srcline, t_program_line* line);
	bool is_comment(string src);
	bool is_label(string src);
};
