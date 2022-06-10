#pragma once
#include "common.h"

struct t_source_line {
	int number;
	string src;
	t_source_line();
	bool operator<(const t_source_line& other) const;
};
