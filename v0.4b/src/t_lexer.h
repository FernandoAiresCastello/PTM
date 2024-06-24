#pragma once
#include "t_string.h"
#include "t_token.h"

class t_lexer
{
public:
	void tokenize_line(const t_string& src, t_list<t_token>& tokens) const;

private:
	const char sym_comment = '#';
	const char sym_space = ' ';
	const char sym_comma = ',';
	const char sym_double_quote = '"';
	const char sym_single_quote = '\'';
	const t_string sym_base_hex = "&H";
	const t_string sym_base_bin = "&B";
	const char sym_positive = '+';
	const char sym_negative = '-';
	const char sym_string_var = '$';
	const char sym_label = ':';
	const char sym_array_open = '[';
	const char sym_array_close = ']';
	const t_string valid_identifier_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._";
	const t_string valid_digits = "0123456789";

	void build_tokens(const t_string& cmd, const t_list<t_string>& args, t_list<t_token>& tokens) const;
};
