#pragma once
#include "t_string.h"

struct t_array_ref {
	bool literal = false;
	t_string arr_name = "";
	t_string arr_subscript_var = "";
	int arr_subscript_lit = 0;
};
