#include "t_source_line.h"

t_source_line::t_source_line() {
}

t_source_line::t_source_line(string file, int line_nr, string text) {
	this->file = file;
	this->text = text;
	this->line_nr = line_nr;
}
