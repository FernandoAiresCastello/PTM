#pragma once
#include "common.h"

enum class t_param_type {
	undefined, number, char_literal, string, id, obj_prop
};
struct t_param {
	string src;
	t_param_type type = t_param_type::undefined;
	string textual_value;
	int numeric_value = 0;
	string id;
	struct {
		string obj_id;
		string name;
	} prop;
};
using t_params = std::vector<t_param>;
