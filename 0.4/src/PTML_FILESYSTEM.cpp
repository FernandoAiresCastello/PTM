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

void PTML::FILE_NAME()
{
	ARGC(2);
	auto&& old_name = STR(1);
	auto&& new_name = STR(2);
	REQUIRE_FILE(old_name);
	VALIDATE_FILENAME(new_name);
	t_filesystem::rename_file(old_name, new_name);
}
