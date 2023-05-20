#pragma once
#include "../Common/common.h"

extern string file_line_delimiter;

string ptm_read_text_file(string path);
vector<string> ptm_read_text_file_lines(string path);
vector<int> ptm_read_binary_file(string path);
void ptm_write_text_file(string path, string text);
void ptm_write_binary_file(string path, vector<int>& bytes);
void ptm_write_binary_file(string path, vector<string>& str_bytes);
