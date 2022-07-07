#include <algorithm>
#include "t_program.h"

t_program::t_program() {
}
void t_program::load_plain(string path) {
	src_lines.clear();
	lines.clear();
	for (auto& src : File::ReadLines(path, "\r\n")) {
		src_lines.push_back(src);
	}
	if (String::Trim(src_lines.back()).empty()) {
		src_lines.pop_back();
	}
}
void t_program::save_plain(string path) {
	File::WriteLines(path, src_lines);
}
void t_program::load_encrypted(string path) {
}
void t_program::save_encrypted(string path) {
}
