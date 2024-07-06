#pragma once

#define CMD(k, fn)				if (cmd == k) return PTML::fn
#define IMM						line->immediate
#define NOT_IMM					!line->immediate
#define REQUIRE_IMM				if (!IMM) { error = err_cmd_not_available; return; }
#define REQUIRE_NOT_IMM			if (IMM) { error = err_cmd_not_available; return; }
#define COUNT(count)			line->argc == count
#define ARGC(count)				if (line->argc != count) { error = err_invalid_argc; return; }
#define ARGC_MIN_MAX(min, max)	if (line->argc < min || line->argc > max) { error = err_invalid_argc; return; }
#define TYPE(n, t)				line->arg##n.type == t
#define NOT_TYPE(n, t)			line->arg##n.type != t
#define STR(n)					resolve_str(line->arg##n)
#define NUM(n)					resolve_num(line->arg##n)
#define REQUIRE_IDENT(n)		if (NOT_TYPE(n, t_token_type::identifier)) { error = err_varname_expected; return; }
#define IDENT(n)				line->arg##n.string_val
#define BOOL(n)					NUM(n) > 0
#define VALIDATE_FILENAME(x)	if (!t_filesystem::is_valid_filename(x)) { error = err_invalid_filename; return; }
#define REQUIRE_FILE(x)			if (!t_filesystem::file_exists(x)) { error = err_file_not_found; return; }
#define EMPTY_STR				""
#define EMPTY_NUM				0
