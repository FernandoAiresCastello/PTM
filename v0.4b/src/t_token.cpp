#include "t_token.h"

t_token::t_token() : 
	type(t_token_type::undefined), string_value(""), numeric_value(0)
{
}

t_token::t_token(t_token_type type, const t_string& value) : 
	type(type), string_value(value), numeric_value(value.to_int())
{
}

t_token::t_token(t_token_type type, int value) : 
	type(type), string_value(value), numeric_value(value)
{
}

t_token::t_token(t_token_type type, const t_string& str_value, int num_value) : 
	type(type), string_value(str_value), numeric_value(num_value)
{
}
