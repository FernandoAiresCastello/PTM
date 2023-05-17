#pragma once
#include <functional>
#include "../PTML/t_param.h"

extern unordered_map<string, function<void(t_params&)>> ptm_commands;

enum {
	CMP_MODE_EQ, CMP_MODE_NEQ,
	CMP_MODE_GT, CMP_MODE_GTE,
	CMP_MODE_LT, CMP_MODE_LTE
};

void ptm_init_commands();
