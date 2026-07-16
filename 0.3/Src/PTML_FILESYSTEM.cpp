#include <stdexcept>
#include "PTML_FILESYSTEM.h"
#include "PTML_GRAPHICS.h"
#include "PTML_shared_headers.h"

#define FILE_EXT_PROGRAM	".PTM"
#define FILE_EXT_CHARSET	".CHR"
#define FILE_EXT_PALETTE	".PAL"
#define FILE_EXT_TILEBUF	".BUF"
#define FILE_EXT_RECFILE	".DAT"

void PTML::SAVE()
{
	ARGC(1);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);

	if (filename.ends_with(FILE_EXT_CHARSET)) {
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

	if (filename.ends_with(FILE_EXT_CHARSET)) {
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

void PTML::CSAVE()
{
	ARGC(2);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);

	t_filesystem::write_all_text(STR(2), filename);
}

void PTML::CLOAD()
{
	ARGC(2);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);

	try {
		t_string content = t_filesystem::read_all_text(filename);
		ptm->set_var(ARG(2), content, error);
	}
	catch (std::exception& ex) {
		error = ex.what();
	}
}

void PTML::BSAVE()
{
	ARGC(2);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);

	auto&& arr_name = ARG(2);
	auto array = ptm->get_array(arr_name.string_val);
	if (array == nullptr) {
		error = err.undefined_array;
		return;
	}

	t_list<int> bytes;

	for (auto& str : *array) {
		int byte = str.to_int();
		if (byte < 0 || byte > 255)
			byte = 0;
		
		bytes.push_back(byte);
	}

	t_filesystem::write_all_bytes(bytes, filename);
}

void PTML::BLOAD()
{
	ARGC(2);

	auto&& filename = STR(1).to_upper();
	VALIDATE_FILENAME(filename);

	try {
		t_list<int> bytes = t_filesystem::read_all_bytes(filename);

		auto&& arr_name = ARG(2);
		t_list<t_string>* array = ptm->create_array(arr_name.string_val);
		for (auto& byte : bytes)
			array->push_back(t_string::from_int(byte));
	}
	catch (std::exception& ex) {
		error = ex.what();
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
