#include "t_program.h"

void t_program::set_line(t_program_line& line)
{
	lines[line.line_nr] = line;
}

bool t_program::delete_line(int line_nr)
{
	bool exists = has_line(line_nr);

	if (exists)
		lines.erase(line_nr);

	return exists;
}

bool t_program::has_line(int line_nr) const
{
	return lines.contains(line_nr);
}

t_program_line* t_program::get_line(int line_nr)
{
	return has_line(line_nr) ? &lines[line_nr] : nullptr;
}

t_string t_program::get_full_source_text()
{
	t_string output;

	for (auto& raw_line : lines) {
		const auto& line = raw_line.second.src;
		int firstSpace = line.index_of(" ");
		output += line.substr(firstSpace).trim();
		output += "\r\n";
	}

	return output;
}

void t_program::renumber_lines(int interval)
{
	int new_line_nr = interval;
	t_ordered_dict<int, t_program_line> new_lines;

	for (const auto& old_line : lines) {
		new_lines[new_line_nr] = old_line.second;
		new_lines[new_line_nr].line_nr = new_line_nr;
		renumber_source_line(new_lines[new_line_nr].src, new_line_nr);
		new_line_nr += interval;
	}

	lines = new_lines;
}

void t_program::renumber_source_line(t_string& line, int new_line_nr)
{
	int&& first_whitespace = line.index_of(" ");
	t_string&& old_line_src = line.substr(first_whitespace).trim();
	line = t_string::from_int(new_line_nr);
	line += " ";
	line += old_line_src;
}

int t_program::find_label(const t_string& label)
{
	for (auto& line : lines) {
		if (line.second.is_label && line.second.label == label) {
			return line.second.line_nr;
		}
	}

	return -1;
}
