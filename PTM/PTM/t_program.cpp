#include <algorithm>
#include "t_program.h"

t_program::t_program() {
}
void t_program::add_line(int number, string src) {
	t_program_line line;
	line.number = number;
	line.src = src;
	lines.push_back(line);
	sort();
}
t_program_line* t_program::get_line(int number) {
	for (auto& line : lines) {
		if (line.number == number) {
			return &line;
		}
	}
	return nullptr;
}
std::vector<string> t_program::get_src_lines() {
	std::vector<string> src;
	for (auto& line : lines) {
		src.push_back(String::Format("%i %s", line.number, line.src.c_str()));
	}
	return src;
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
void t_program::sort() {
	std::sort(lines.begin(), lines.end());
}
void t_program::renumerate(int increment) {
	sort();
	int new_number = 0;
	for (int i = 0; i < lines.size(); i++) {
		new_number += increment;
		lines[i].number = new_number;
	}
}
