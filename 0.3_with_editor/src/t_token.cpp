#include "t_token.h"

t_token::t_token() : 
	type(t_token_type::invalid), string_val(""), numeric_val(0)
{
}

t_token::t_token(t_token_type type, const t_string& value) : 
	type(type), string_val(value), numeric_val(value.to_int())
{
}

t_token::t_token(t_token_type type, int value) : 
	type(type), string_val(value), numeric_val(value)
{
}

t_token::t_token(t_token_type type, const t_string& str_value, int num_value) : 
	type(type), string_val(str_value), numeric_val(num_value)
{
}
