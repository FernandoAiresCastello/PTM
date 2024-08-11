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

void PTML::FILE_REN()
{
	ARGC(2);
	auto&& old_name = STR(1);
	auto&& new_name = STR(2);
	VALIDATE_FILENAME(new_name);
	REQUIRE_FILE(old_name);
	t_filesystem::rename_file(old_name, new_name);
}

void PTML::FILE_DEL()
{
	ARGC(1);
	auto&& name = STR(1);
	VALIDATE_FILENAME(name);
	REQUIRE_FILE(name);
	t_filesystem::delete_file(name);
}

void PTML::DIR_REN()
{
	ARGC(2);
	auto&& old_name = STR(1);
	auto&& new_name = STR(2);
	VALIDATE_FILENAME(new_name);
	REQUIRE_DIR(old_name);
	t_filesystem::rename_directory(old_name, new_name);
}

void PTML::DIR_DEL()
{
	ARGC(1);
	auto&& name = STR(1);
	VALIDATE_FILENAME(name);
	REQUIRE_DIR(name);
	bool deleted = t_filesystem::delete_directory(name);
	if (!deleted) {
		error = err.filesystem_error;
		return;
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

void PTML::DIR_Q()
{
	ARGC(0);
	scr->print_string_crlf(t_filesystem::get_current_directory());
}
