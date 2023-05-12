#include "t_variable.h"

t_variable::t_variable() : t_variable("", false) {
}
t_variable::t_variable(string value, bool is_const) {
	this->value = value;
	this->is_const = is_const;
}
t_variable::t_variable(int value, bool is_const) {
	this->value = String::ToString(value);
	this->is_const = is_const;
}
