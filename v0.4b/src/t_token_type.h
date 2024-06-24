#pragma once

enum class t_token_type
{
	invalid = -1,
	undefined,
	line_number,
	command,
	label,
	identifier,
	literal_num,
	literal_str,
	literal_char,
};
