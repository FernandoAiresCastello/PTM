#pragma once
#include "common.h"

struct t_environment {
	std::map<string, string> vars;
	bool has_var(string var);
};
