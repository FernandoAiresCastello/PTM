#include "PTML.h"
#include "PTM.h"
#include "t_util.h"
#include "t_screen.h"
#include "t_window.h"
#include "t_program_line.h"
#include "t_filesystem.h"

const t_string err_invalid_argc = "Invalid argument count";
const t_string err_varname_expected = "Variable name expected";
const t_string err_undefined_var = "Undefined variable";
const t_string err_division_by_zero = "Division by zero";
const t_string err_undefined_line_nr = "Undefined line number";
const t_string err_label_not_found = "Label not found";
const t_string err_cmd_not_available = "Command not available";
const t_string err_file_not_found = "File not found";
const t_string err_invalid_filename = "Illegal filename";

PTM* ptm = nullptr;
t_screen* scr = nullptr;
t_program_line* line = nullptr;
t_string PTML::error;

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
#define EMPTY_STR				""
#define EMPTY_NUM				0

void PTML::set_env(PTM* _ptm, t_screen* _scr) { ptm = _ptm; scr = _scr;}
void PTML::set_line(t_program_line* _line) { line = _line; }

static const t_string resolve_str(const t_param& arg)
{
	if (arg.type == t_token_type::invalid)
		return EMPTY_STR;
	if (arg.type == t_token_type::identifier)
		return ptm->has_var(arg.string_val) ? ptm->get_var_str(arg.string_val) : EMPTY_STR;

	return arg.string_val;
}

static int resolve_num(const t_param& arg)
{
	if (arg.type == t_token_type::invalid)
		return EMPTY_NUM;
	if (arg.type == t_token_type::identifier)
		return ptm->has_var(arg.string_val) ? ptm->get_var_num(arg.string_val) : EMPTY_NUM;

	return arg.numeric_val;
}

//=============================================================================
//									COMMANDS
//=============================================================================

void PTML::COLOR()
{
	ARGC_MIN_MAX(1, 3);

	if (COUNT(3)) {
		scr->color_fg(NUM(1));
		scr->color_bg(NUM(2));
		scr->color_bdr(NUM(3));
	}
	else if (COUNT(2)) {
		scr->color_fg(NUM(1));
		scr->color_bg(NUM(2));
	}
	else if (COUNT(1)) {
		scr->color_fg(NUM(1));
	}
}

void PTML::COLOR_F()
{
	ARGC(1);
	scr->color_fg(NUM(1));
}

void PTML::COLOR_B()
{
	ARGC(1);
	scr->color_bg(NUM(1));
}

void PTML::COLOR_BD()
{
	ARGC(1);
	scr->color_bdr(NUM(1));
}

void PTML::VAR()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), STR(2));
}

void PTML::VARS()
{
	ARGC(0);
	for (auto& var : ptm->get_vars()) {
		scr->println(t_string::fmt("%s: %s", var.first.c_str(), var.second.c_str()));
	}
}

void PTML::PRINT()
{
	ARGC(1);
	auto&& value = STR(1);

	if (IMM && !value.empty())
		scr->println(value);
	else
		scr->print(value);
}

void PTML::PRINTL()
{
	ARGC(1);
	auto&& value = STR(1);
	scr->println(value);
}

void PTML::EXIT()
{
	ARGC(0);
	ptm->exit();
}

void PTML::HALT()
{
	ARGC(0);
	ptm->halt();
}

void PTML::CLS()
{
	ARGC(0);
	scr->clear();
	scr->locate(0, 0);
}

void PTML::PAL()
{
	ARGC(2);
	ptm->get_pal().set(NUM(1), NUM(2));
}

void PTML::CHR()
{
	ARGC(3);
	ptm->get_chr().set_row(NUM(1), NUM(2), STR(3));
}

void PTML::LOCATE()
{
	ARGC(2);
	scr->locate(NUM(1), NUM(2));
}

void PTML::INC()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), ptm->get_var_num(IDENT(1)) + 1);
}

void PTML::DEC()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), ptm->get_var_num(IDENT(1)) - 1);
}

void PTML::ADD()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2))
		ptm->set_var(IDENT(1), NUM(1) + NUM(2));
	else if (COUNT(3))
		ptm->set_var(IDENT(1), NUM(2) + NUM(3));
}

void PTML::SUB()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2))
		ptm->set_var(IDENT(1), NUM(1) - NUM(2));
	else if (COUNT(3))
		ptm->set_var(IDENT(1), NUM(2) - NUM(3));
}

void PTML::MUL()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2))
		ptm->set_var(IDENT(1), NUM(1) * NUM(2));
	else if (COUNT(3))
		ptm->set_var(IDENT(1), NUM(2) * NUM(3));
}

void PTML::DIV()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2)) {
		int divisor = NUM(2);
		if (divisor == 0)
			error = err_division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(1) / divisor);
	}
	else if (COUNT(3)) {
		int divisor = NUM(3);
		if (divisor == 0)
			error = err_division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(2) / divisor);
	}
}

void PTML::DIVR()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2)) {
		int divisor = NUM(2);
		if (divisor == 0)
			error = err_division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(1) % divisor);
	}
	else if (COUNT(3)) {
		int divisor = NUM(3);
		if (divisor == 0)
			error = err_division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(2) % divisor);
	}
}

void PTML::POW()
{
	ARGC(3);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), (int)pow((float)NUM(2), (float)NUM(3)));
}

void PTML::SQRT()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), (int)sqrt((float)NUM(2)));
}

void PTML::RND()
{
	ARGC_MIN_MAX(1, 3);
	REQUIRE_IDENT(1);

	if (COUNT(3))
		ptm->set_var(IDENT(1), t_util::rnd(NUM(2), NUM(3)));
	else if (COUNT(2))
		ptm->set_var(IDENT(1), t_util::rnd(NUM(2)));
	else if (COUNT(1))
		ptm->set_var(IDENT(1), t_util::rnd(0, INT_MAX));
}

void PTML::SWAP()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	REQUIRE_IDENT(2);
	const t_string val1 = STR(1);
	const t_string val2 = STR(2);
	ptm->set_var(IDENT(1), val2);
	ptm->set_var(IDENT(2), val1);
}

void PTML::FSCR()
{
	ARGC_MIN_MAX(0, 1);

	if (COUNT(1))
		ptm->get_wnd().set_fullscreen(BOOL(1));
	else if (COUNT(0))
		ptm->get_wnd().toggle_fullscreen();
}

void PTML::CSR_SET()
{
	ARGC(1);
	scr->show_cursor(BOOL(1));
}

void PTML::TILE_NEW()
{
	ARGC_MIN_MAX(0, 3);
	
	ptm->get_tilereg().set_empty();

	if (COUNT(0))
		return;
	else if (COUNT(3))
		ptm->get_tilereg().add_char(NUM(1), NUM(2), NUM(3));
	else
		error = err_invalid_argc;
}

void PTML::TILE_ADD()
{
	ARGC(3);
	ptm->get_tilereg().add_char(NUM(1), NUM(2), NUM(3));
}

void PTML::TILE_LIST()
{
	ARGC(0);
	for (auto&& ch : ptm->get_tilereg().get_all_chars()) {
		scr->println(t_string::fmt("%i, %i, %i", ch.ix, ch.fgc, ch.bgc));
	}
}

void PTML::PUT()
{
	if (!ptm->get_tilereg().has_any_char())
		return;

	ARGC_MIN_MAX(0, 2);

	if (COUNT(0)) {
		if (IMM) {
			scr->newline();
			scr->set_tile(ptm->get_tilereg(), 0, scr->csry() - 1);
		}
		else {
			scr->set_tile_at_csr(ptm->get_tilereg());
		}
	}
	else if (COUNT(2))
		scr->set_tile(ptm->get_tilereg(), NUM(1), NUM(2));
	else
		error = err_invalid_argc;
}

void PTML::GET()
{
	ARGC_MIN_MAX(0, 2);

	if (COUNT(0)) {
		if (NOT_IMM) {
			ptm->set_tilereg(scr->get_tile_at_csr());
		}
	}
	else if (COUNT(2))
		ptm->set_tilereg(scr->get_tile(t_pos(NUM(1), NUM(2))));
	else
		error = err_invalid_argc;
}

void PTML::LIST()
{
	ARGC_MIN_MAX(0, 2);

	if (COUNT(0)) {
		for (auto& stored_line : ptm->get_prg().lines) {
			scr->println(stored_line.second.to_string());
		}
	}
	else if (COUNT(1)) {
		t_program& prg = ptm->get_prg();
		int line_nr = NUM(1);
		if (prg.has_line(line_nr)) {
			scr->println(prg.get_line(line_nr)->to_string());
		}
		else {
			error = err_undefined_line_nr;
		}
	}
	else if (COUNT(2)) {
		auto& lines = ptm->get_prg().lines;
		int first = NUM(1);
		int last = NUM(2);
		auto itLower = lines.lower_bound(first);
		auto itUpper = lines.upper_bound(last);
		for (auto& it = itLower; it != itUpper; ++it) {
			scr->println(it->second.to_string());
		}
	}
}

void PTML::RUN()
{
	REQUIRE_IMM;
	ARGC(0);
	ptm->run_program();
}

void PTML::END()
{
	ARGC(0);
	ptm->end_program();
}

void PTML::NEW()
{
	REQUIRE_IMM;
	ARGC(0);
	ptm->new_program();
}

void PTML::SAVE()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	ptm->save_program(filename);
}

void PTML::LOAD()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	if (t_filesystem::file_exists(filename))
		ptm->load_program(filename);
	else
		error = err_file_not_found;
}

void PTML::FILES()
{
	ARGC(0);
	for (auto& file : t_filesystem::list_files())
		scr->println(file);
}

void PTML::GOTO()
{
	REQUIRE_NOT_IMM;
	ARGC(1);
	REQUIRE_IDENT(1);

	auto& label = IDENT(1);
	if (ptm->has_program_label(label))
		ptm->goto_program_label(label);
	else
		error = err_label_not_found;
}

void PTML::GOTO_IFE()
{
	REQUIRE_NOT_IMM;
	ARGC(3);

	auto&& a = STR(1);
	auto&& b = STR(2);

	if (a == b) {
		REQUIRE_IDENT(3);
		auto&& label = IDENT(3);
		if (ptm->has_program_label(label))
			ptm->goto_program_label(label);
		else
			error = err_label_not_found;
	}
}

void PTML::GOTO_IFNE()
{
}

void PTML::GOTO_IFG()
{
}

void PTML::GOTO_IFGE()
{
}

void PTML::GOTO_IFL()
{
}

void PTML::GOTO_IFLE()
{
}
