#pragma once
#include "common.h"

struct t_variable {
	string value;
	bool is_const;
	t_variable();
	t_variable(string value, bool is_const = false);
	t_variable(int value, bool is_const = false);
};
