#pragma once
#include "t_list.h"
#include "t_string.h"
#include "t_token.h"
#include "t_program_line.h"
#include "t_function_ptr.h"

class t_parser
{
public:
	t_list<t_string> errors;

	t_program_line parse_line(const t_list<t_token>& tokens);

private:
	t_function_ptr get_fn_by_cmd(const t_string& cmd);
};
