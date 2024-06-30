#pragma once
#include "t_string.h"
#include "t_list.h"

class t_program;
class t_interpreter;

class t_filesystem
{
public:
	static bool is_valid_filename(const t_string& filename);
	static bool file_exists(const t_string& filename);
	static t_list<t_string> list_files();
	static t_string read_all_text(const t_string& filename);
	static t_list<t_string> read_all_lines(const t_string& filename);
	static void write_all_text(t_string text, const t_string& filename);
	static void save_program(t_program* prg, const t_string& filename);
	static void load_program(t_interpreter* intp, t_program* prg, const t_string& filename);

	static t_list<t_string> illegal_filenames;
};
