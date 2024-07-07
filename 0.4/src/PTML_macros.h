#pragma once

#define CMD(k, fn)				if (cmd == k) return PTML::fn
#define IMM						line->immediate
#define NOT_IMM					!line->immediate
#define REQUIRE_IMM				if (!IMM) { error = err.cmd_not_available; return; }
#define REQUIRE_NOT_IMM			if (IMM) { error = err.cmd_not_available; return; }
#define COUNT(count)			line->argc == count
#define ARGC(count)				if (line->argc != count) { error = err.invalid_argc; return; }
#define ARGC_MIN_MAX(min, max)	if (line->argc < min || line->argc > max) { error = err.invalid_argc; return; }
#define TYPE(n, t)				line->arg##n.type == t
#define NOT_TYPE(n, t)			line->arg##n.type != t
#define STR(n)					resolve_str(line->arg##n)
#define NUM(n)					resolve_num(line->arg##n)
#define REQUIRE_IDENT(n)		if (NOT_TYPE(n, t_token_type::identifier)) { error = err.varname_expected; return; }
#define REQUIRE_LABEL(n)		if (NOT_TYPE(n, t_token_type::identifier)) { error = err.label_expected; return; }
#define IDENT(n)				line->arg##n.string_val
#define BOOL(n)					NUM(n) > 0
#define VALIDATE_FILENAME(x)	if (!t_filesystem::is_valid_filename(x)) { error = err.invalid_filename; return; }
#define REQUIRE_FILE(x)			if (!t_filesystem::file_exists(x)) { error = err.file_not_found; return; }
#define EMPTY_STR				""
#define EMPTY_NUM				0
#define TILEREG					ptm->tilereg
#define IF_TILEREG_EMPTY_RET	if (!TILEREG.has_any_char()) return
