#include "t_tokenizer.h"

void t_tokenizer::tokenize_line(t_string& src, t_list<t_token>& tokens)
{
	ptr = 0;
	squote = false;
	dquote = false;
	tokens.clear();
	src = src.trim();

	if (src.empty())
		return;

	t_list<t_string> parts;
	while (has_next_part(src)) {
		t_string&& part = next_part(src);
		if (part.empty())
			continue;

		parts.push_back(part);
	}

	for (int i = 0; i < parts.size(); i++) {
		auto& part = parts[i];
		t_token&& token = parse_token(i, part);
		tokens.push_back(token);
		if (token.type == t_token_type::comment || token.type == t_token_type::label)
			break;
	}
}

bool t_tokenizer::has_next_part(t_string& line) const
{
	return ptr < line.length();
}

t_string t_tokenizer::next_part(t_string& line)
{
	t_string str;
	if (squote && !dquote) str += sym.single_quote;
	if (dquote && !squote) str += sym.double_quote;

	while (ptr < line.length()) {
		const char& ch = line[ptr++];
		if ((ch == sym.space || ch == sym.tab || ch == sym.comma) && !squote && !dquote) {
			break;
		}
		if (ch == sym.double_quote && !squote) {
			dquote = !dquote;
			if (!dquote) str += sym.double_quote;
			break;
		}
		if (ch == sym.single_quote && !dquote) {
			squote = !squote;
			if (!squote) str += sym.single_quote;
			break;
		}
		str += ch;
	}

	return str;
}

t_token t_tokenizer::parse_token(int token_index, t_string& src)
{
	t_token token;
	token.src = src;
	t_string src_upper = src.to_upper();

	// ===== NUMBER LITERAL =====
	if (isdigit(src[0]) || src[0] == sym.positive || src[0] == sym.negative ||
		src_upper.starts_with(sym.base_hex) || src_upper.starts_with(sym.base_bin)) {
		token.type = token_index == 0 ? t_token_type::line_number : t_token_type::literal_num;
		token.numeric_val = src.to_int();
		token.string_val = t_string::from_int(token.numeric_val);
	}
	// ===== STRING LITERAL =====
	else if (src.starts_and_ends_with(sym.double_quote)) {
		token.type = t_token_type::literal_str;
		token.string_val = src.remove_first_and_last();
		token.numeric_val = token.string_val.to_int();
	}
	// ===== CHARACTER LITERAL =====
	else if (src.starts_and_ends_with(sym.single_quote)) {
		auto&& val = src.remove_first_and_last();
		if (val.length() != 1) {
			token.type = t_token_type::invalid;
		}
		else {
			token.type = t_token_type::literal_char;
			token.numeric_val = val[0];
			token.string_val = t_string::from_int(token.numeric_val);
		}
	}
	// ===== ARRAY REFERENCE =====
	else if (src.contains(sym.array_sub_begin) && src.contains(sym.array_sub_end)) {
		int ix_begin = src.index_of(sym.array_sub_begin);
		int ix_end = src.index_of(sym.array_sub_end);
		if (ix_begin < ix_end - 1) {
			auto&& arr_name = src.substr(0, ix_begin - 1);
			if (arr_name.empty()) {
				token.type = t_token_type::invalid;
				token.string_val = src;
			}
			else {
				token.array_ref.arr_name = arr_name;
				auto&& subscript_part = src.substr(ix_begin);
				auto&& subscript = subscript_part.remove_first_and_last();
				auto&& subscript_upper = subscript.to_upper();

				if (isalpha(subscript[0])) {
					token.type = t_token_type::array_subscript_variable;
					token.array_ref.literal = false;
					token.array_ref.arr_subscript_var = subscript;
				}
				else if (isdigit(subscript[0]) || subscript[0] == sym.positive || subscript[0] == sym.negative || 
					subscript_upper.starts_with(sym.base_hex) || subscript_upper.starts_with(sym.base_bin)) {

					token.type = t_token_type::array_subscript_literal;
					token.array_ref.literal = true;
					token.array_ref.arr_subscript_lit = subscript.to_int();
				}
				else {
					token.type = t_token_type::invalid;
					token.string_val = src;
				}
			}
		}
		else {
			token.type = t_token_type::invalid;
			token.string_val = src;
		}
	}
	// ===== COMMENT =====
	else if (src.starts_with(sym.comment)) {
		token.type = t_token_type::comment;
	}
	// ===== LABEL =====
	else if (src.ends_with(sym.label)) {
		auto&& val = src.substr(0, src.length() - 2);
		if (val.empty()) {
			token.type = t_token_type::invalid;
		}
		else {
			token.type = t_token_type::label;
			token.string_val = val;
		}
	}
	// ===== COMMAND / IDENTIFIER =====
	else if (src_upper.contains_only(sym.valid_identifier_chars)) {
		token.type = t_token_type::command_or_identifier;
		token.string_val = src;
	}
	// ===== INVALID =====
	else {
		token.type = t_token_type::invalid;
		token.string_val = src;
	}

	return token;
}
