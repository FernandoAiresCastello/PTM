#pragma once
#include "t_function_ptr.h"
#include "t_param.h"
#include "t_string.h"

class t_program_line
{
public:
	const int undefined_line_nr = -1;

	int src_line_nr = undefined_line_nr;
	t_string src;
	bool has_error = false;
	t_function_ptr fn = nullptr;
	int argc = 0;
	t_param arg1;
	t_param arg2;
	t_param arg3;
	t_param arg4;
	t_param arg5;

	t_program_line& operator=(const t_program_line& other);
};
