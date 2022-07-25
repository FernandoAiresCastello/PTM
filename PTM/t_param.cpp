#include "t_param.h"

bool t_param::is_array() {
	return type == t_param_type::arr_ix_literal || type == t_param_type::arr_ix_var;
}
