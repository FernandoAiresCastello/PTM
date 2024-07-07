#pragma once
#include "t_string.h"

namespace PTML
{
	struct {
		const t_string syntax_error = "Syntax error";
		const t_string invalid_argc = "Invalid argument count";
		const t_string varname_expected = "Variable name expected";
		const t_string undefined_var = "Undefined variable";
		const t_string division_by_zero = "Division by zero";
		const t_string undefined_line_nr = "Undefined line number";
		const t_string label_not_found = "Label not found";
		const t_string label_expected = "Label expected";
		const t_string cmd_not_available = "Command not available";
		const t_string file_not_found = "File not found";
		const t_string invalid_filename = "Illegal filename";
		const t_string arg_out_of_range = "Out of range";
		const t_string invalid_program = "Invalid program";
	}
	err;
}
