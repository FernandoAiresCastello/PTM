#pragma once
#include "../Common/common.h"

struct t_source_line {
	string file;
	string text;
	int line_nr = 0;
	t_source_line();
	t_source_line(string file, int line_nr, string text);
};
