#include "ptm_filesystem.h"

string file_line_delimiter = "\r\n";

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
