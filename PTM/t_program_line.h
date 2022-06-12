#pragma once
#include "common.h"

struct t_source_line;

struct t_program_line {
	t_source_line* src;
	string cmd;
	std::vector<string> args;
	std::vector<int> code;
	t_program_line();
};
