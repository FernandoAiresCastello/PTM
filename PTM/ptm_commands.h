#pragma once
#include <functional>
#include "Compiler/t_param.h"

extern unordered_map<string, function<void(t_params&)>> cmap;

void ptm_init_commands();
