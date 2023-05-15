#pragma once
#include <functional>
#include "Compiler/t_param.h"

extern unordered_map<string, function<void(t_params&)>> ptm_commands;

void ptm_init_commands();
