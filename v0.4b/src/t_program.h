#pragma once
#include "t_dict.h"
#include "t_program_line.h"

class t_program
{
public:
	t_ordered_dict<int, t_program_line> lines;

	void set_line(t_program_line& line);
};
