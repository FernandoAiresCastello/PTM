#pragma once
#include "t_string.h"
#include "t_token.h"
#include "PTM.h"

class t_tokenizer
{
public:
	void tokenize_line(t_string& src, t_list<t_token>& tokens);

private:
	const struct {
		char comment = '#';
		char space = ' ';
		char tab = '\t';
		char comma = ',';
		char double_quote = '"';
		char single_quote = '\'';
		t_string base_hex = "&H";
		t_string base_bin = "&B";
		char positive = '+';
		char negative = '-';
		char label = ':';
		t_string valid_identifier_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._";
		t_string valid_digits = "0123456789";

	} sym;

	int ptr = 0;
	bool squote = false;
	bool dquote = false;

	bool has_next_part(t_string& line) const;
	t_string next_part(t_string& line);
	t_token parse_token(int token_index, t_string& src);
};
