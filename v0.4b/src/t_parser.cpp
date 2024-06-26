#include "t_parser.h"
#include "PTML.h"

#define CMD(keyword)	if (cmd == #keyword) return PTML::keyword;

t_program_line t_parser::parse_line(const t_list<t_token>& tokens)
{
	errors.clear();
	
	t_program_line line;
	const t_token_type& type = tokens[0].type;

	if (type == t_token_type::command) {
		const t_string& cmd = tokens[0].string_value;
		line.fn = get_fn_by_cmd(cmd);
		line.argc = int(tokens.size() - 1);
		
		if (line.argc > 0) {
			line.arg1.is_identifier = tokens[1].type == t_token_type::identifier;
			line.arg1.string_val = tokens[1].string_value;
			line.arg1.numeric_val = tokens[1].numeric_value;
		}
		if (line.argc > 1) {
			line.arg2.is_identifier = tokens[2].type == t_token_type::identifier;
			line.arg2.string_val = tokens[2].string_value;
			line.arg2.numeric_val = tokens[2].numeric_value;
		}
		if (line.argc > 2) {
			line.arg3.is_identifier = tokens[3].type == t_token_type::identifier;
			line.arg3.string_val = tokens[3].string_value;
			line.arg3.numeric_val = tokens[3].numeric_value;
		}
		if (line.argc > 3) {
			line.arg4.is_identifier = tokens[4].type == t_token_type::identifier;
			line.arg4.string_val = tokens[4].string_value;
			line.arg4.numeric_val = tokens[4].numeric_value;
		}
		if (line.argc > 4) {
			line.arg5.is_identifier = tokens[5].type == t_token_type::identifier;
			line.arg5.string_val = tokens[5].string_value;
			line.arg5.numeric_val = tokens[5].numeric_value;
		}
	}

	return line;
}

t_function_ptr t_parser::get_fn_by_cmd(const t_string& cmd)
{
	CMD(COLOR);
	CMD(VARS);
	CMD(PEEK);
	CMD(VAR);
	CMD(EXIT);

	return nullptr;
}
