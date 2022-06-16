#pragma once
#include "common.h"

struct t_game {
	std::map<string, string> vars;
	bool has_var(string var);
	string get_var(string var);
};
