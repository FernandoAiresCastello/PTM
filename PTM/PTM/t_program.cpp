#include "t_program.h"

t_program::t_program() {
}
void t_program::add_line(int number, string code) {
	t_program_line line;
	line.number = number;
	line.code = code;
	lines.push_back(line);
}
bool t_program::delete_line(int number) {
	int curIndex = 0;
	int index = -1;
	for (auto& line : lines) {
		if (line.number == number) {
			index = curIndex;
			break;
		}
		curIndex++;
	}
	if (index >= 0) {
		lines.erase(lines.begin() + index);
		return true;
	}
	return false;
}
bool t_program::has_line_number(int number) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].number == number) {
			return true;
		}
	}
	return false;
}
