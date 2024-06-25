#pragma once
#include "t_string.h"

struct t_param
{
	bool is_identifier = false;
	t_string string_val = "";
	int numeric_val = 0;
};