#pragma once
#include "common.h"

enum class t_param_type {
	undefined, number, string, variable, label
};
struct t_param {
	string src;
	t_param_type type = t_param_type::undefined;
	string string_literal;
	int number_literal = 0;
	string label;
	string variable;
	int array_index_literal = 0;
	string array_index_variable;
	string resolved_variable;
};
using t_params = std::vector<t_param>;
