#pragma once
#include "t_function_ptr.h"
#include "t_param.h"
#include "t_string.h"

class t_program_line
{
public:
	bool immediate = false;
	bool is_label = false;
	bool is_comment = false;
	bool has_error = false;
	int line_nr = -1;
	t_string label;
	t_string src;
	t_function_ptr fn = nullptr;
	int argc = 0;
	t_param arg1;
	t_param arg2;
	t_param arg3;
	t_param arg4;
	t_param arg5;

	t_program_line& operator=(const t_program_line& other);

	const t_string& to_string() const;
};
