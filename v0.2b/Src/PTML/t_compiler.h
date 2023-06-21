#pragma once
#include "../Common/common.h"

struct t_program;
struct t_program_line;
struct t_source_line;

struct t_compiler {
	vector<string> errors;
	void run(t_program* prg);
	bool has_window_def;
	struct {
		int width = 0;
		int height = 0;
		int size = 0;
		int default_buf_layer_count = 1;
	} window_def;
private:
	bool compile_line(t_program* prg, t_program_line* new_line, t_source_line* src_line_ptr);
	int parse_number(string arg);
	void add_error(t_source_line* line, string msg);
	void add_syntax_error(t_source_line* line);
	bool is_invalid_line_start(string& src_line);
	bool has_leading_whitespace(string& src_line);
	bool is_comment(string& src_line);
	bool is_label(string& src_line);
	vector<string> parse_args(string& raw_args);
	bool has_sign(string& arg);
	bool is_number(string& arg);
	bool is_string_literal(string& arg);
	bool is_char_literal(string& arg);
	bool is_variable_identifier(string& arg);
	bool is_array_identifier(string& arg);
	bool is_if_block_start(string& arg);
	bool is_if_block_end(string& arg);
	bool is_endfor(string& arg);
	bool is_window_def(string& arg);
	bool is_data(string& arg);
	bool is_ptm_version_directive(string& arg);
};
