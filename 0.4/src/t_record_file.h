#pragma once
#include "t_string.h"
#include "t_list.h"

#define RECFILE_STATE_OK		0
#define RECFILE_STATE_BADFMT	1

class t_record_file
{
public:
	char mode = 0;
	bool is_open = false;
	t_string filename;
	static char delimiter;
	int state = RECFILE_STATE_OK;

	int open(const t_string& filename, char mode);
	void close_and_save_text_file();
	void write(const t_string& data);
	void write(int data);
	void write(bool data);
	void write(const t_list<t_string>& data);
	t_string read();
	bool is_eof();

private:
	t_list<t_string> buffer;
	int ptr = 0;

	void read_file_into_buffer(const t_string& filename);
};
