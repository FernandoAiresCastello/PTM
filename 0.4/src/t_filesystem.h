#pragma once
#include "t_string.h"
#include "t_list.h"

class t_program;
class t_interpreter;
class t_charset;
class t_palette;
class t_screen;

class t_filesystem
{
public:
	static const char read_mode = 'R';
	static const char write_mode = 'W';

	static t_list<t_string> illegal_filenames;
	static bool is_valid_filename(const t_string& filename);
	static bool file_exists(const t_string& filename);
	static bool directory_exists(const t_string& name);
	static t_list<t_string> list_files(const char* prefix = nullptr);
	static t_list<t_string> find_files(const t_string& namepart);
	static void write_hex_file(const t_string& data, const t_string& filename);
	static t_string read_hex_file(const t_string& filename);
	static t_string read_all_text(const t_string& filename);
	static t_list<t_string> read_all_lines(const t_string& filename);
	static void write_all_text(const t_string& text, const t_string& filename);
	static void write_all_lines(const t_list<t_string>& lines, const t_string& filename);
	static bool rename_file(const t_string& old_name, const t_string& new_name);
	static bool delete_file(const t_string& name);
	static bool rename_directory(const t_string& old_name, const t_string& new_name);
	static bool delete_directory(const t_string& name);
	static void save_program_plaintext(t_program* prg, const t_string& filename);
	static void load_program_plaintext(t_interpreter* intp, t_program* prg, const t_string& filename);
	static void save_program_binary(t_program* prg, const t_string& filename);
	static void load_program_binary(t_interpreter* intp, t_program* prg, const t_string& filename);
	static void create_directory(const t_string& dir);
	static void change_directory(const t_string& dir);
	static const t_string& get_current_directory();
	static const t_string& get_root_directory();
	static void save_charset(t_charset* chr, const t_string& filename);
	static void save_palette(t_palette* pal, const t_string& filename);
	static void load_charset(t_charset* chr, const t_string& filename);
	static void load_palette(t_palette* pal, const t_string& filename);
	static bool is_record_file_open();
	static char get_record_file_mode();
	static void open_record_file(const t_string& filename, char mode);
	static void close_record_file();
	static void write_record_file(const t_string& data);
	static t_string read_record_file();
	static bool is_record_file_eof();
};
