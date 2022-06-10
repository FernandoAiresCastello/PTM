#pragma once
#include "common.h"

struct t_source_line;

struct t_program_line {
	t_source_line* src;
	t_program_line();
};
