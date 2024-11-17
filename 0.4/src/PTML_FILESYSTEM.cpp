#include <stdexcept>
#include "PTML_FILESYSTEM.h"
#include "PTML_shared_headers.h"

void PTML::FILES()
{
	ARGC_MIN_MAX(0, 1);
	if (COUNT(0)) {
		PRINT_LIST(t_filesystem::list_files());
	}
	else if (COUNT(1)) {
		PRINT_LIST(t_filesystem::find_files(STR(1)));
	}
}

void PTML::RENAME()
{
	ARGC(2);
	auto&& old_name = STR(1);
	auto&& new_name = STR(2);
	VALIDATE_FILENAME(new_name);

	if (t_filesystem::file_exists(old_name)) {
		t_filesystem::rename_file(old_name, new_name);
	}
	else if (t_filesystem::directory_exists(old_name)) {
		t_filesystem::rename_directory(old_name, new_name);
	}
	else {
		error = err.file_not_found;
	}
}

void PTML::KILL()
{
	ARGC(1);
	auto&& name = STR(1);

	if (t_filesystem::file_exists(name)) {
		t_filesystem::delete_file(name);
	}
	else if (t_filesystem::directory_exists(name)) {
		t_filesystem::delete_directory(name);
	}
	else {
		error = err.file_not_found;
	}
}

void PTML::CHDIR()
{
	ARGC_MIN_MAX(0, 1);
	auto&& name = COUNT(0) ? "" : STR(1);

	if (name.trim().empty() || name == t_filesystem::get_root_directory()) {
		name = "";
	}
	else {
		VALIDATE_FILENAME(name);
		REQUIRE_DIR(name);
	}

	t_filesystem::change_directory(name);
}

void PTML::MKDIR()
{
	ARGC(1);
	auto&& name = STR(1);
	VALIDATE_FILENAME(name);
	ASSERT_DIR_NOT_FOUND(name);

	if (t_filesystem::file_exists(name)) {
		error = err.cant_create_directory;
		return;
	}

	t_filesystem::create_directory(name);
}

void PTML::OPEN_W()
{
	ARGC(1);
	auto&& name = STR(1);
	VALIDATE_FILENAME(name);
	if (t_filesystem::is_record_file_open()) {
		error = err.file_already_open;
		return;
	}
	t_filesystem::open_record_file(name, t_filesystem::write_mode);
}

void PTML::OPEN_R()
{
	ARGC(1);
	auto&& name = STR(1);
	VALIDATE_FILENAME(name);
	REQUIRE_FILE(name);
	if (t_filesystem::is_record_file_open()) {
		error = err.file_already_open;
		return;
	}
	
	int state = t_filesystem::open_record_file(name, t_filesystem::read_mode);
	if (state == RECFILE_STATE_BADFMT) {
		error = err.bad_file_format;
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
	REQUIRE_IDENT(1);
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
	ptm->set_var(IDENT(1), t_filesystem::read_record_file());
}

void PTML::FEOF()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), t_filesystem::is_record_file_eof() ? 1 : 0);
}
