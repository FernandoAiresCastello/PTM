#pragma once
#include "common.h"

struct t_loop {
	int line_ix_begin = 0;
	string var;
	int current = 0;
	int first = 0;
	int last = 0;
	int step = 0;
};
