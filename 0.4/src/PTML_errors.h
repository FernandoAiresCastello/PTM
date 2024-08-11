#pragma once
#include "t_string.h"

namespace PTML
{
	struct {
		const t_string syntax_error = "Syntax error";
		const t_string invalid_argc = "Invalid argument count";
		const t_string varname_expected = "Variable name expected";
		const t_string undefined_var = "Undefined variable";
		const t_string tilebuf_not_found = "Tile buffer not found";
		const t_string division_by_zero = "Division by zero";
		const t_string undefined_line_nr = "Undefined line number";
		const t_string label_not_found = "Label not found";
		const t_string label_expected = "Label expected";
		const t_string cmd_not_available = "Command not available";
		const t_string file_not_found = "File not found";
		const t_string directory_not_found = "Directory not found";
		const t_string cant_create_directory = "Could not create directory";
		const t_string cant_create_file = "Could not create file";
		const t_string invalid_filename = "Illegal filename";
		const t_string arg_out_of_range = "Out of bounds";
		const t_string invalid_program = "Invalid program";
		const t_string unknown_keyname = "Unknown key name";
		const t_string unknown_fn_keyname = "Function key name expected";
		const t_string sprite_not_found = "Sprite not found";
		const t_string table_not_found = "Table not found";
		const t_string tile_preset_not_found = "Tile preset not found";
		const t_string filesystem_error = "Filesystem error";
	}
	err;
}
