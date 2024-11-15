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
	t_string get_full_source_text();
	void renumber_lines(int interval);
	int find_label(const t_string& label);

private:
	void renumber_source_line(t_string& line, int new_line_nr);
};
