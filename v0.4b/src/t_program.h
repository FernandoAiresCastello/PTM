#pragma once
#include "t_dict.h"
#include "t_program_line.h"

class t_program
{
public:
	t_ordered_dict<int, t_program_line> lines;

	void set_line(t_program_line& line);
	bool delete_line(int line_nr);
	bool has_line(int line_nr) const;
	t_program_line* get_line(int line_nr);
};
