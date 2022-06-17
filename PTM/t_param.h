#pragma once
#include "common.h"

enum class t_param_type {
	undefined, number, char_literal, string, label, address_alias, address_deref_literal, address_deref_alias
};
struct t_param {
	string src;
	t_param_type type = t_param_type::undefined;
	string textual_value;
	int numeric_value = 0;
	string label;
	string address_alias;
	int address = ILLEGAL_ADDRESS;
};
using t_params = std::vector<t_param>;
