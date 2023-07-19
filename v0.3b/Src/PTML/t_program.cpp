#include <algorithm>
#include "t_program.h"

t_program::t_program() {
}
void t_program::clear() {
	src_lines.clear();
	lines.clear();
	labels.clear();
}
bool assert_filesys_path(string path)
{
	path = String::Replace(path, "/", "\\");
	auto parts = String::Split(path, "\\", true);
	for (auto& part : parts) {
		if (String::StartsWith(part, ".") || String::Contains(path, ":")) {
			MsgBox::Error(PTM_MSGBOX_TITLE, "Illegal file path included: " + path);
			return false;
		}
	}
	return true;
}
bool t_program::load_plain(string path) {
	if (!File::Exists(path)) {
		MsgBox::Error(PTM_MSGBOX_TITLE, String::Format("Program file not found:\n\n%s", path.c_str()));
		return false;
	}
	clear();
	int line_nr = 0;
	for (auto& src : File::ReadLines(path, "\r\n")) {
		line_nr++;
		string trim_line = String::Trim(src);
		if (String::StartsWith(String::ToUpper(trim_line), "INCL")) {
			string incl_filename = String::Trim(String::Skip(trim_line, 4));
			if (!assert_filesys_path(incl_filename)) {
				return false;
			}
			if (File::Exists(incl_filename)) {
				int incl_line_nr = 0;
				for (auto& incl_line_text : File::ReadLines(incl_filename, "\r\n")) {
					incl_line_nr++;
					src_lines.push_back(t_source_line(incl_filename, incl_line_nr, incl_line_text));
				}
			} else {
				MsgBox::Error(PTM_MSGBOX_TITLE, String::Format("Included file not found:\n\n%s", incl_filename.c_str()));
				return false;
			}
		} else {
			src_lines.push_back(t_source_line(path, line_nr, src));
		}
	}
	if (String::Trim(src_lines.back().text).empty()) {
		src_lines.pop_back();
	}
	file = path;
	return true;
}
