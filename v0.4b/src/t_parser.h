#pragma once
#include "t_list.h"
#include "t_string.h"
#include "t_token.h"

class t_parser
{
public:
	t_list<t_string> errors;

	void parse(const t_list<t_token>& tokens);
};
