#pragma once
#include "t_list.h"
#include "t_string.h"

class t_table
{
public:
	void init(int cols, int rows);

	int get_cols() const { return cols; }
	int get_rows() const { return rows; }

	void set(int col, int row, const t_string& value);
	void set(int col, int row, int value);
	t_string& get(int col, int row);
	int get_int(int col, int row);

private:
	int cols = 0;
	int rows = 0;
	int length = 0;

	t_list<t_string> data;
};
