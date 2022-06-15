#pragma once
#include "common.h"

enum class t_param_type {
	undefined, number, string, variable, index, label
};

struct t_param {
	string src;
	t_param_type type = t_param_type::undefined;
	string string_literal;
	int number_literal = 0;
	string label;
	string variable;
	int index = 0;
	string resolved_variable;
};
