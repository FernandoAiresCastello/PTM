#include "t_table.h"

void t_table::init(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
	this->length = cols * rows;

	data.clear();
	for (int i = 0; i < length; i++) {
		data.emplace_back("");
	}
}

void t_table::set(int col, int row, const t_string& value)
{
	data[(size_t)(row * cols + col)] = value;
}

void t_table::set(int col, int row, int value)
{
	set(col, row, t_string::from_int(value));
}

t_string& t_table::get(int col, int row)
{
	return data[(size_t)(row * cols + col)];
}

int t_table::get_int(int col, int row)
{
	return get(col, row).to_int();
}
