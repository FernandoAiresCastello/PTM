#pragma once
#include "../Common/common.h"

extern string file_line_delimiter;
extern string record_file_delimiter;

string ptm_read_text_file(string path);
vector<string> ptm_read_text_file_lines(string path);
void ptm_write_text_file_lines(string path, vector<string>& lines);
vector<int> ptm_read_binary_file(string path);
void ptm_write_text_file(string path, string text);
void ptm_write_binary_file(string path, vector<int>& bytes);
void ptm_write_binary_file(string path, vector<string>& str_bytes);
void ptm_open_record_file(string path, char mode);
void ptm_save_record_file(string path);
bool ptm_is_end_of_record_file();
int ptm_get_record_file_item_count();
void ptm_write_to_record_file(string value);
void ptm_write_to_record_file(int value);
string ptm_read_string_from_record_file();
int ptm_read_int_from_record_file();
char ptm_get_record_file_mode();
