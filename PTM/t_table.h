#pragma once
#include "common.h"

struct t_table {
	t_table();
	t_table(int cols, int rows);
	void resize(int cols, int rows);
	void clear();
	void set_value(int col, int row, int value);
	void set_value(int col, int row, string value);
	string get_value_as_string(int col, int row);
	int get_value_as_number(int col, int row);
	int get_col_count();
	int get_row_count();
private:
	int rows = 0;
	int cols = 0;
	std::vector<string> data;
};
