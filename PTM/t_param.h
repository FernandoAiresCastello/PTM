#pragma once
#include "common.h"

enum class t_param_type {
	undefined, number, string, variable, label, object
};
struct t_param {
	string src;
	t_param_type type = t_param_type::undefined;
	string textual_value;
	int numeric_value = 0;
	string label;
	string variable;
	string object_id;
};
using t_params = std::vector<t_param>;
