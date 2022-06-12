#include "t_source_line.h"

t_source_line::t_source_line() {
	number = 0;
	src = "";
}
bool t_source_line::operator<(const t_source_line& other) const {
	return number < other.number;
}
