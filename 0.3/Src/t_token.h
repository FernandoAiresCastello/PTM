#pragma once
#include "t_token_type.h"
#include "t_array_ref.h"
#include "t_string.h"

struct t_token
{
	t_token_type type = t_token_type::invalid;
	t_string src;
	t_string string_val;
	int numeric_val;
	t_array_ref array_ref;

	t_token();
	t_token(t_token_type type, const t_string& value);
	t_token(t_token_type type, int value);
	t_token(t_token_type type, const t_string& str_value, int num_value);
};
