#include "PTML_FILESYSTEM.h"
#include "PTML_shared_headers.h"

void PTML::FILES()
{
	ARGC(0);
	scr->print_lines(t_filesystem::list_files());
}

void PTML::FILE_NAME()
{
	ARGC(2);
	auto&& old_name = STR(1);
	auto&& new_name = STR(2);
	REQUIRE_FILE(old_name);
	VALIDATE_FILENAME(new_name);
	t_filesystem::rename_file(old_name, new_name);
}

