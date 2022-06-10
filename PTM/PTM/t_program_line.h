#pragma once
#include "common.h"

struct t_program_line {
	int number;
	string src;
	t_program_line();
	bool operator<(const t_program_line& other) const;
};
