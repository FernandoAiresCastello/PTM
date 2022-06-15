#include <algorithm>
#include "t_program.h"

t_program::t_program() {
}
void t_program::load(string path) {
	src_lines.clear();
	lines.clear();
	for (auto& src : File::ReadLines(path, "\r\n")) {
		src_lines.push_back(src);
	}
}
