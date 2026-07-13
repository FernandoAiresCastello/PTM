#include <stdexcept>
#include "PTML_FILESYSTEM.h"
#include "PTML_GRAPHICS.h"
#include "PTML_shared_headers.h"

#define FILE_EXT_PROGRAM	".PTM"
#define FILE_EXT_CHARSET	".CHR"
#define FILE_EXT_PALETTE	".PAL"
#define FILE_EXT_TILEBUF	".BUF"
#define FILE_EXT_RECFILE	".DAT"

void PTML::FILES()
{
	ARGC_MIN_MAX(0, 1);
	if (COUNT(0)) {
		PRINT_LIST(t_filesystem::list_user_files());
	}
	else if (COUNT(1)) {
		PRINT_LIST(t_filesystem::find_user_files(STR(1)));
	}
}

void PTML::RENAME()
{
	ARGC(2);
	auto&& old_name = STR(1);
	auto&& new_name = STR(2);
	VALIDATE_FILENAME(new_name);

	if (t_filesystem::user_file_exists(old_name)) {
		t_filesystem::rename_user_file(old_name, new_name);
	}
	else {
		error = err.file_not_found;
	}
}

void PTML::KILL()
{
	ARGC(1);
	auto&& name = STR(1).to_upper();

	if (t_filesystem::user_file_exists(name)) {
		t_filesystem::delete_user_file(name);
	}
	else {
		error = err.file_not_found;
	}
}

void PTML::OPEN()
{
	ARGC(2);
	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);
	auto&& mode = STR(2).to_upper();

	if (!filename.ends_with(FILE_EXT_RECFILE)) {
		error = err.invalid_file_ext;
		return;
	}

	if (t_filesystem::is_record_file_open()) {
		error = err.file_already_open;
		return;
	}

	if (mode == "W") {
		t_filesystem::open_record_file(filename, t_filesystem::write_mode);
	}
	else if (mode == "R") {
		REQUIRE_FILE(filename);
		int state = t_filesystem::open_record_file(filename, t_filesystem::read_mode);
		if (state == RECFILE_STATE_BADFMT) {
			error = err.bad_file_format;
			return;
		}
	}
	else {
		error = err.illegal_argument;
		return;
	}
}

void PTML::CLOSE()
{
	ARGC(0);
	t_filesystem::close_record_file();
}

void PTML::WRITE()
{
	ARGC(1);
	if (!t_filesystem::is_record_file_open()) {
		error = err.file_not_open;
		return;
	}
	if (t_filesystem::get_record_file_mode() != t_filesystem::write_mode) {
		error = err.bad_file_mode;
		return;
	}
	t_filesystem::write_record_file(STR(1));
}

void PTML::READ()
{
	ARGC(1);
	if (!t_filesystem::is_record_file_open()) {
		error = err.file_not_open;
		return;
	}
	if (t_filesystem::get_record_file_mode() != t_filesystem::read_mode) {
		error = err.bad_file_mode;
		return;
	}
	if (t_filesystem::is_record_file_eof()) {
		error = err.end_of_file;
		return;
	}
	ptm->set_var(ARG(1), t_filesystem::read_record_file(), error);
}

void PTML::FEOF()
{
	ARGC(1);
	ptm->set_var(ARG(1), t_filesystem::is_record_file_eof() ? 1 : 0, error);
}

void PTML::SAVE()
{
	ARGC(1);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);

	if (filename.ends_with(FILE_EXT_PROGRAM)) {
		REQUIRE_IMM;
		if (ptm->get_prg().lines.empty()) {
			error = err.invalid_program;
			return;
		}
		ptm->save_program(filename);
	}
	else if (filename.ends_with(FILE_EXT_CHARSET)) {
		SAVE_CHR();
	}
	else if (filename.ends_with(FILE_EXT_PALETTE)) {
		SAVE_PAL();
	}
	else if (filename.ends_with(FILE_EXT_TILEBUF)) {
		SAVE_BUF();
	}
	else {
		error = err.invalid_file_ext;
		return;
	}
}

void PTML::LOAD()
{
	ARGC(1);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	if (filename.ends_with(FILE_EXT_PROGRAM)) {
		REQUIRE_IMM;
		bool valid = try_load_program(filename);
		if (!valid) {
			error = err.invalid_program;
			return;
		}
	}
	else if (filename.ends_with(FILE_EXT_CHARSET)) {
		LOAD_CHR();
	}
	else if (filename.ends_with(FILE_EXT_PALETTE)) {
		LOAD_PAL();
	}
	else if (filename.ends_with(FILE_EXT_TILEBUF)) {
		LOAD_BUF();
	}
	else {
		error = err.invalid_file_ext;
		return;
	}
}
