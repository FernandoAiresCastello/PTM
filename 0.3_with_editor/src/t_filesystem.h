#pragma once
#include "t_string.h"
#include "t_list.h"
#include "t_record_file.h"

#define SYS_ROOT            "SYS/"
#define USER_ROOT           "USR/"
#define PROGRAM_FILE_EXT    ".PTM"
#define AUTOEXEC_FILE       "AUTOEXEC" PROGRAM_FILE_EXT
#define AUTOSAVE_FILE       "AUTOSAVE" PROGRAM_FILE_EXT
#define DEF_CHARSET_FILE    "DEFAULT.CHR"
#define DEF_PALETTE_FILE    "DEFAULT.PAL"

class t_program;
class t_interpreter;
class t_charset;
class t_palette;
class t_screen;

class t_filesystem
{
public:

	// Validation
	static t_list<t_string> illegal_filenames;
	static bool is_valid_filename(const t_string& filename);
	static bool file_exists(const t_string& filename);
	static bool user_file_exists(const t_string& filename);

	// Listing
	static t_list<t_string> list_user_files(const char* prefix = nullptr);
	static t_list<t_string> find_user_files(const t_string& namepart);
	
	// Write/read hex format
	static void write_hex_file(const t_string& data, const t_string& filename);
	static t_string read_hex_file(const t_string& filename);

	// Write/read plaintext format
	static t_string read_all_text(const t_string& filename);
	static t_list<t_string> read_all_lines(const t_string& filename);
	static void write_all_text(const t_string& text, const t_string& filename);
	static void write_all_lines(const t_list<t_string>& lines, const t_string& filename);
	
	// Rename/delete
	static bool rename_user_file(const t_string& old_name, const t_string& new_name);
	static bool delete_user_file(const t_string& name);
	static bool rename_directory(const t_string& old_name, const t_string& new_name);
	static bool delete_directory(const t_string& name);

	// Program files
	static bool has_autoexec_file();
	static t_string get_autoexec_file();
	static void autosave_program(t_program* prg);
	static void save_program_plaintext(t_program* prg, const t_string& filename);
	static void load_program_plaintext(t_interpreter* intp, t_program* prg, const t_string& filename);

	// Charset/palette files
	static void save_charset_plaintext(t_charset* chr, const t_string& filename);
	static void save_palette_plaintext(t_palette* pal, const t_string& filename);
	static void load_charset_plaintext(t_charset* chr, const t_string& filename);
	static void load_palette_plaintext(t_palette* pal, const t_string& filename);

	static void load_default_charset(t_charset* chr);
	static void load_default_palette(t_palette* pal);

	// Record files
	static const char read_mode = 'R';
	static const char write_mode = 'W';

	static bool is_record_file_open();
	static char get_record_file_mode();
	static int open_record_file(const t_string& filename, char mode);
	static void close_record_file();
	static void write_record_file(const t_string& data);
	static t_string read_record_file();
	static bool is_record_file_eof();
};
