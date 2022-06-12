#pragma once
#include "common.h"

struct t_program;
struct t_source_line;
struct t_program_line;

struct t_compiler {
	void run(t_program* prg);
private:
	void parse_src_line(t_program* prg, t_source_line* srcline, t_program_line* line);
	void compile(t_program_line* line);
};
