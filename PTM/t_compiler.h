#pragma once
#include "common.h"

struct t_program;
struct t_source_line;

struct t_compiler {
	void compile(t_program* prg);
private:
	void compile_line(t_program* prg, t_source_line* srcline);
};
