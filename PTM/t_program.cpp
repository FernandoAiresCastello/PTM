#include <algorithm>
#include "t_program.h"
#include "t_obfuscator.h"

t_program::t_program() {
}
void t_program::clear() {
	src_lines.clear();
	lines.clear();
	labels.clear();
}
bool t_program::load_plain(string path) {
	clear();
	int line_nr = 0;
	for (auto& src : File::ReadLines(path, "\r\n")) {
		line_nr++;
		if (src[0] == '#') {
			string incl_filename = String::Trim(String::Skip(src, 1));
			if (File::Exists(incl_filename)) {
				auto incl_lines = File::ReadLines(incl_filename, "\r\n");
				src_lines.insert(src_lines.end(), incl_lines.begin(), incl_lines.end());
			} else {
				MsgBox::Error("PTM", String::Format("Included file not found: %s", incl_filename.c_str()));
				return false;
			}
		} else {
			src_lines.push_back(src);
		}
	}
	if (String::Trim(src_lines.back()).empty()) {
		src_lines.pop_back();
	}
	return true;
}
void t_program::save_plain(string path) {
	File::WriteLines(path, src_lines);
}
void t_program::load_encrypted(string path) {
	clear();
	auto file_lines = File::ReadLines(path, "\r\n");
	t_obfuscator::xor_decrypt(&file_lines, &src_lines);
	if (String::Trim(src_lines.back()).empty()) {
		src_lines.pop_back();
	}
}
void t_program::save_encrypted(string path) {
	auto encrypted = t_obfuscator::xor_encrypt(&src_lines);
	File::WriteLines(path, encrypted);
}
