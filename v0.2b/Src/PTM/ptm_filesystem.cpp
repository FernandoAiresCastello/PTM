#include "ptm_filesystem.h"

string file_line_delimiter = "\r\n";
string record_file_delimiter = "§";
vector<string> record_file_input;
string record_file_output;
string record_file_path;
char record_file_mode = 0;
int record_file_ptr = PTM_INVALID_NUMBER;

string ptm_read_text_file(string path)
{
	return File::ReadText(path);
}
vector<string> ptm_read_text_file_lines(string path)
{
	return File::ReadLines(path, file_line_delimiter);
}
vector<int> ptm_read_binary_file(string path)
{
	return File::ReadBytesAsIntegers(path);
}
void ptm_write_text_file(string path, string text)
{
	File::WriteText(path, text);
}
void ptm_write_binary_file(string path, vector<int>& bytes)
{
	File::WriteIntegersAsBytes(path, bytes);
}
void ptm_write_binary_file(string path, vector<string>& str_bytes)
{
	vector<int> bytes;
	for (auto& str : str_bytes) {
		bytes.push_back(String::ToInt(str));
	}
	File::WriteIntegersAsBytes(path, bytes);
}
void ptm_open_record_file(string path, char mode)
{
	record_file_path = path;
	mode = toupper(mode);
	record_file_mode = mode;

	if (record_file_mode == 'R') {
		string file = ptm_read_text_file(path);
		record_file_input = String::Split(file, record_file_delimiter, false);
		record_file_ptr = 0;
	}
	else if (record_file_mode == 'W') {
		record_file_output.clear();
		record_file_ptr = PTM_INVALID_NUMBER;
	}
}
void ptm_save_record_file(string path)
{
	if (record_file_mode == 'W') {
		record_file_output = String::RemoveLast(record_file_output);
		File::WriteText(path, record_file_output);
		record_file_output.clear();
	}
}
bool ptm_is_end_of_record_file()
{
	return record_file_ptr < 0 || record_file_ptr >= record_file_input.size();
}
int ptm_get_record_file_item_count()
{
	return record_file_input.size();
}
void ptm_write_to_record_file(string value)
{
	if (record_file_mode == 'W') {
		record_file_output += value + record_file_delimiter;
	}
}
void ptm_write_to_record_file(int value)
{
	ptm_write_to_record_file(String::ToString(value));
}
string ptm_read_string_from_record_file()
{
	if (record_file_mode == 'R') {
		return record_file_input[record_file_ptr++];
	}
	return "";
}
int ptm_read_int_from_record_file()
{
	return String::ToInt(ptm_read_string_from_record_file());
}
char ptm_get_record_file_mode()
{
	return record_file_mode;
}
