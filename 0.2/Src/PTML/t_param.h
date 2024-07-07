#pragma once
#include "../Common/common.h"

enum class t_param_type {
	undefined, number, char_literal, string, id, arr_ix_literal, arr_ix_var
};
struct t_param {
	string src;
	t_param_type type = t_param_type::undefined;
	string textual_value;
	int numeric_value = 0;
	string id;
	int arr_ix_literal = -1;
	string arr_ix_var;
	bool is_array_element_ix();
};
using t_params = vector<t_param>;
