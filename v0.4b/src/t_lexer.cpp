#include "t_lexer.h"

void t_lexer::tokenize_line(const t_string& src, t_list<t_token>& tokens) const
{
	tokens.clear();
	t_string line = src.trim();
	if (line.empty() || line.starts_with(sym_comment))
		return;

	t_string cmd;
	t_list<t_string> args;

	int i = 0;
	bool done = false;
	bool is_label = false;

	while (!done && i < src.length()) {

		const char ch = src[i++];
		is_label = ch == sym_label;

		if (ch == sym_space || is_label) {
			done = true;
			break;
		}
		cmd += ch;
	}

	if (cmd.contains_only(valid_digits)) {

		tokens.push_back(t_token(t_token_type::line_number, cmd, cmd.to_int()));
		cmd = "";
		done = false;

		while (!done && i < src.length()) {

			const char ch = src[i++];
			if (ch == sym_space) {
				done = true;
				break;
			}
			cmd += ch;
		}
	}
	else if (is_label) {
		cmd += sym_label;
	}

	bool inside_double_quote = false;
	bool inside_single_quote = false;
	t_string arg;

	done = false;
	while (!done && i < src.length()) {

		const char ch = src[i++];

		if (ch == sym_comma && !inside_double_quote && !inside_single_quote) {
			if (!arg.empty())
				args.push_back(arg.trim());

			arg = "";
			continue;
		}

		arg += ch;

		if (ch == sym_double_quote) {
			inside_double_quote = !inside_double_quote;
			continue;
		}
		if (ch == sym_single_quote) {
			inside_single_quote = !inside_single_quote;
			continue;
		}
	}
	if (!arg.empty())
		args.push_back(arg.trim());

	build_tokens(cmd, args, tokens);
}

void t_lexer::build_tokens(const t_string& cmd, const t_list<t_string>& args, t_list<t_token>& tokens) const
{
	if (cmd.ends_with(sym_label)) {
		tokens.push_back(t_token(t_token_type::label, cmd.substr(0, (int)(cmd.length() - 2))));
		return;
	}
	else {
		tokens.push_back(t_token(t_token_type::command, cmd.to_upper()));
	}

	for (auto& arg : args) {
		t_string arg_upper = arg.to_upper();

		if (isdigit(arg[0]) || arg[0] == sym_positive || arg[0] == sym_negative || 
			arg_upper.starts_with(sym_base_hex) || arg_upper.starts_with(sym_base_bin)) {

			tokens.push_back(t_token(t_token_type::literal_num, arg));
		}
		else if (arg.starts_and_ends_with(sym_double_quote)) {
			tokens.push_back(t_token(t_token_type::literal_str, arg.remove_first_and_last()));
		}
		else if (arg.starts_and_ends_with(sym_single_quote) && arg.length() == 3) {
			tokens.push_back(t_token(t_token_type::literal_char, arg[1], arg[1]));
		}
		else if (arg.to_upper().contains_only(valid_identifier_chars)) {
			tokens.push_back(t_token(t_token_type::identifier, arg));
		}
		else {
			tokens.push_back(t_token(t_token_type::invalid, arg));
		}
	}
}
