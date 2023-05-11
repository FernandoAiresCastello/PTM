#include <algorithm>
#include "t_program.h"
#include "t_obfuscator.h"

t_program::t_program() {
}
void t_program::clear() {
	src_lines.clear();
	lines.clear();
	labels.clear();
	data.clear();
}
bool t_program::load_plain(string path) {
	clear();
	int line_nr = 0;
	for (auto& src : File::ReadLines(path, "\r\n")) {
		line_nr++;
		string trim_line = String::Trim(src);
		if (String::StartsWith(String::ToUpper(trim_line), "INCL")) {
			string incl_filename = String::Trim(String::Skip(trim_line, 4));
			if (File::Exists(incl_filename)) {
				int incl_line_nr = 0;
				for (auto& incl_line_text : File::ReadLines(incl_filename, "\r\n")) {
					incl_line_nr++;
					src_lines.push_back(t_source_line(incl_filename, incl_line_nr, incl_line_text));
				}
			} else {
				MsgBox::Error("PTM", String::Format("Included file not found:\n\n%s", incl_filename.c_str()));
				return false;
			}
		} else {
			src_lines.push_back(t_source_line(path, line_nr, src));
		}
	}
	if (String::Trim(src_lines.back().text).empty()) {
		src_lines.pop_back();
	}
	return true;
}
