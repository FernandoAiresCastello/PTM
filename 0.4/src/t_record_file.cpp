#include "t_record_file.h"
#include "t_filesystem.h"

void t_record_file::open(const t_string& filename, char mode)
{
	is_open = true;
	this->filename = filename;
	this->mode = mode;
	ptr = 0;

	if (mode == t_filesystem::read_mode)
		read_file_into_buffer();
	else
		buffer.clear();
}

void t_record_file::read_file_into_buffer()
{
	buffer = t_filesystem::read_hex_file(filename).split(delimiter);
}

void t_record_file::close_and_save_hex_file()
{
	is_open = false;

	if (mode == t_filesystem::write_mode) {
		t_string&& data = t_string::join(buffer, delimiter);
		t_filesystem::write_hex_file(data, filename);
	}

	mode = 0;
}

void t_record_file::close_and_save_text_file()
{
	is_open = false;

	if (mode == t_filesystem::write_mode) {
		t_string&& data = t_string::join(buffer, delimiter);
		t_filesystem::write_all_text(data, filename);
	}

	mode = 0;
}

void t_record_file::write(const t_string& data)
{
	buffer.push_back(data);
}

void t_record_file::write(int data)
{
	buffer.push_back(t_string::from_int(data));
}

void t_record_file::write(bool data)
{
	buffer.push_back(t_string::from_int(data ? 1 : 0));
}

void t_record_file::write(const t_list<t_string>& data)
{
	buffer = data;
}

t_string t_record_file::read()
{
	return buffer[ptr++];
}

bool t_record_file::is_eof()
{
	return ptr < 0 || ptr >= buffer.size();
}
