#pragma once
#include "t_string.h"
#include "t_token.h"
#include "t_token_type.h"
#include "t_array_ref.h"

struct t_param
{
	t_token_type type = t_token_type::invalid;
	t_string string_val = "";
	int numeric_val = 0;
	t_array_ref array_ref;

	t_param() = default;

	t_param(const t_token& token) : 
		type(token.type), string_val(token.string_val), numeric_val(token.numeric_val),
		array_ref(token.array_ref)
	{
		if (type == t_token_type::command_or_identifier)
			type = t_token_type::identifier;
	}

	bool is_array() const
	{
		return type == t_token_type::array_subscript_literal || 
			   type == t_token_type::array_subscript_variable;
	}

	bool is_ident() const
	{
		return type == t_token_type::identifier || 
			   type == t_token_type::command_or_identifier;
	}
};
