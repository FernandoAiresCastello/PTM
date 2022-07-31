#include "t_table.h"

t_table::t_table() {
}
t_table::t_table(int cols, int rows) {
	resize(cols, rows);
}
void t_table::resize(int cols, int rows) {
	this->cols = cols;
	this->rows = rows;
	data.clear();
	for (int i = 0; i < cols * rows; i++) {
		data.push_back("");
	}
}
void t_table::clear() {
	for (int i = 0; i < cols * rows; i++) {
		data[i] = "";
	}
}
void t_table::set_value(int col, int row, int value) {
	set_value(col, row, String::ToString(value));
}
void t_table::set_value(int col, int row, string value) {
	data[row * cols + col] = value;
}
int t_table::get_value_as_number(int col, int row) {
	return String::ToInt(get_value_as_string(col, row));
}
string t_table::get_value_as_string(int col, int row) {
	return data[row * cols + col];
}
int t_table::get_col_count() {
	return cols;
}
int t_table::get_row_count() {
	return rows;
}
