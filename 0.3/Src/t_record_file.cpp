#include <stdexcept>
#include "t_record_file.h"
#include "t_filesystem.h"

char t_record_file::delimiter = '§';

int t_record_file::open(const t_string& filename, char mode)
{
	state = RECFILE_STATE_OK;

	if (mode == t_filesystem::read_mode)
		read_file_into_buffer(filename);
	else
		buffer.clear();

	if (state == RECFILE_STATE_OK) {
		this->filename = filename;
		this->mode = mode;
		is_open = true;
		ptr = 0;
	}

	return state;
}

void t_record_file::read_file_into_buffer(const t_string& filename)
{
	t_string&& text = t_filesystem::read_all_text(filename);

	if (text.starts_and_ends_with(t_string(delimiter))) {
		state = RECFILE_STATE_OK;
		t_string&& records = text.substr(1, text.length() - 1);
		buffer = records.split(delimiter, false);
	}
	else {
		state = RECFILE_STATE_BADFMT;
		return;
	}
}

void t_record_file::close_and_save_text_file()
{
	is_open = false;

	if (mode == t_filesystem::write_mode) {
		t_string&& data = t_string(delimiter) + t_string::join(buffer, delimiter) + t_string(delimiter);
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

int t_record_file::read_int()
{
	return read().to_int();
}

bool t_record_file::is_eof()
{
	return ptr < 0 || ptr >= buffer.size() || !is_open;
}
