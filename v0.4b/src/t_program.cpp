#include "t_program.h"

void t_program::set_line(t_program_line& line)
{
	lines[line.line_nr] = line;
}

bool t_program::delete_line(int line_nr)
{
	bool exists = has_line(line_nr);

	if (exists)
		lines.erase(line_nr);

	return exists;
}

bool t_program::has_line(int line_nr) const
{
	return lines.contains(line_nr);
}

t_program_line* t_program::get_line(int line_nr)
{
	return has_line(line_nr) ? &lines[line_nr] : nullptr;
}
