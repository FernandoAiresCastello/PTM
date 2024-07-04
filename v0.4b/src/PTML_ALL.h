#pragma once
#include "t_string.h"
#include "t_function_ptr.h"

namespace PTML
{
	t_function_ptr get_cmd_pointer(const t_string& cmd);
}
