#pragma once

enum class t_token_type
{
	invalid,
	line_number,
	comment,
	label,
	command_or_identifier,
	identifier,
	literal_num,
	literal_str,
	literal_char
};
