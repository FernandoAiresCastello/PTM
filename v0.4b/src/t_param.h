#pragma once
#include "t_string.h"

struct t_param
{
	t_token_type type = t_token_type::undefined;
	t_string string_val = "";
	int numeric_val = 0;
};