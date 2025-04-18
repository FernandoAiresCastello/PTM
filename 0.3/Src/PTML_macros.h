#pragma once

#define CMD(k, fn)				if (cmd == k) { return PTML::fn; }
#define IMM						line->immediate
#define NOT_IMM					!line->immediate
#define REQUIRE_IMM				if (!IMM) { error = err.cmd_not_available; return; }
#define REQUIRE_NOT_IMM			if (IMM) { error = err.cmd_not_available; return; }
#define COUNT(count)			line->argc == count
#define ARGC(count)				if (line->argc != count) { error = err.invalid_argc; return; }
#define ARGC_MIN_MAX(min, max)	if (line->argc < min || line->argc > max) { error = err.invalid_argc; return; }
#define ARG(n)					line->arg##n
#define TYPE(n, t)				line->arg##n.type == t
#define NOT_TYPE(n, t)			line->arg##n.type != t
#define STR(n)					resolve_str(line->arg##n)
#define NUM(n)					resolve_num(line->arg##n)
#define NUM_WRAP(n, max)		(resolve_num(line->arg##n) % max)
#define REQUIRE_LABEL(n)		if (NOT_TYPE(n, t_token_type::identifier)) { error = err.label_expected; return; }
#define IDENT(n)				line->arg##n.string_val
#define BOOL(n)					NUM(n) > 0
#define VALIDATE_FILENAME(x)	if (!t_filesystem::is_valid_filename(x)) { error = err.invalid_filename; return; }
#define REQUIRE_FILE(x)			if (!t_filesystem::user_file_exists(x)) { error = err.file_not_found; return; }
#define EMPTY_STR				""
#define EMPTY_NUM				0
#define TILEREG					ptm->tilereg
#define SOUND					ptm->get_sound()
#define TILEREG_OR_BLANK_TILE	(ptm->tilereg.has_any_char() ? TILEREG : scr->create_blank_tile())
#define IF_TILEREG_EMPTY_RET	if (!TILEREG.has_any_char()) { return; }
#define PRINT_LIST(x)			if (scr->print_lines(x, ptm)) { scr->print_string_crlf("Break"); }
#define CHK_TBUF_BOUNDS(x, col, row)		if (col < 0 || row < 0 || col > x->last_col || row > x->last_row) { error = err.arg_out_of_range; return; }
#define REQUIRE_SPRITE(x)		if (x < 0 || x >= t_spritelist::max_sprites) { error = err.invalid_sprite_number; return; }
#define TILEBUF(x)				auto&& buf = get_tilebuffer(x); if (buf == nullptr) { return; }
#define CHK_TBL_BOUNDS(x, col, row)		if (col < 0 || row < 0 || col >= x.get_cols() || row >= x.get_rows()) { error = err.arg_out_of_range; return; }
#define PAL_SIZE				ptm->get_pal().size()
#define CHR_SIZE				ptm->get_chr().size()
