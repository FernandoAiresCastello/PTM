#include "t_program_line.h"

t_program_line::t_program_line() {
	number = 0;
	src = "";
}
bool t_program_line::operator<(const t_program_line& other) const {
	return number < other.number;
}
