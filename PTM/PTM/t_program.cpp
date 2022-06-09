#include "t_program.h"

t_program::t_program() {
}
void t_program::add_line(int number, string code) {
	t_program_line line;
	line.number = number;
	line.code = code;
	lines.push_back(line);
}
