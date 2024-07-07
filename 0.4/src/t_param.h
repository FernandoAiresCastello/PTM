#pragma once
#include "t_string.h"
#include "t_token.h"
#include "t_token_type.h"

struct t_param
{
	t_token_type type = t_token_type::invalid;
	t_string string_val = "";
	int numeric_val = 0;

	t_param() = default;

	t_param(const t_token& token) : type(token.type), string_val(token.string_val), numeric_val(token.numeric_val)
	{
		if (type == t_token_type::command_or_identifier)
			type = t_token_type::identifier;
	}
};
