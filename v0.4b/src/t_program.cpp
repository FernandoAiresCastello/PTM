#include "t_program.h"

void t_program::set_line(t_program_line& line)
{
	lines[line.src_line_nr] = line;
}
