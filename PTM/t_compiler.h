#pragma once
#include "common.h"

struct t_program;
struct t_program_line;
struct t_source_line;

struct t_compiler {
	std::vector<string> errors;
	void run(t_program* prg);
private:
	bool compile_line(t_program* prg, t_program_line* new_line, t_source_line* src_line_ptr);
	void add_error(t_source_line* line, string msg);
	void add_syntax_error(t_source_line* line);
	bool is_invalid_line_start(string& src_line);
	bool has_leading_whitespace(string& src_line);
	bool is_comment(string& src_line);
	bool is_label(string& src_line);
	std::vector<string> parse_args(string& raw_args);
	bool is_number(string& arg);
	bool is_string_literal(string& arg);
	bool is_char_literal(string& arg);
	bool is_variable_identifier(string& arg);
	bool is_array_identifier(string& arg);
	bool is_if(string& arg);
	bool is_endif(string& arg);
	bool is_endfor(string& arg);
};
