#include "t_program_line.h"
#include "PTML_ALL.h"

t_program_line::t_program_line()
{
}

t_program_line::t_program_line(const t_list<t_token>& tokens)
{
	const t_token_type& type = tokens[0].type;

	if (type == t_token_type::command_or_identifier || 
		type == t_token_type::array_subscript_literal ||
		type == t_token_type::array_subscript_variable) {

		const t_string& cmd = tokens[0].string_val.to_upper();
		fn = PTML::get_cmd_pointer(cmd);
		argc = int(tokens.size() - 1);

		if (argc > 0) arg1 = t_param(tokens[1]);
		if (argc > 1) arg2 = t_param(tokens[2]);
		if (argc > 2) arg3 = t_param(tokens[3]);
		if (argc > 3) arg4 = t_param(tokens[4]);
		if (argc > 4) arg5 = t_param(tokens[5]);
		if (argc > 5) arg6 = t_param(tokens[6]);
	}
	else if (type == t_token_type::label) {
		is_label = true;
		label = tokens[0].string_val;
	}
	else if (type == t_token_type::comment) {
		is_comment = true;
	}

	for (auto& token : tokens) {
		if (token.type == t_token_type::invalid) {
			has_error = true;
			break;
		}
	}
}

t_program_line& t_program_line::operator=(const t_program_line& other)
{
    if (this == &other)
        return *this;

    immediate = other.immediate;
    is_label = other.is_label;
    is_comment = other.is_comment;
    label = other.label;
    line_nr = other.line_nr;
    src = other.src;
    has_error = other.has_error;
    fn = other.fn;
    argc = other.argc;
    arg1 = other.arg1;
    arg2 = other.arg2;
    arg3 = other.arg3;
    arg4 = other.arg4;
    arg5 = other.arg5;
	arg6 = other.arg6;

    return *this;
}

const t_string& t_program_line::to_string() const
{
    return src;
}
