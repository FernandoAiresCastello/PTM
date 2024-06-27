#include "PTML.h"
#include "PTM.h"
#include "t_util.h"
#include "t_screen.h"
#include "t_window.h"
#include "t_program_line.h"

const t_string err_invalid_argc = "Invalid argument count";
const t_string err_varname_expected = "Variable name expected";
const t_string err_undefined_var = "Undefined variable";
const t_string err_division_by_zero = "Division by zero";

PTM* ptm = nullptr;
t_screen* scr = nullptr;
t_program_line* line = nullptr;
t_string PTML::error;

#define IMM						line->src_line_nr == line->undefined_line_nr
#define COUNT(count)			line->argc == count
#define ARGC(count)				if (line->argc != count) { error = err_invalid_argc; return; }
#define ARGC_MIN_MAX(min, max)	if (line->argc < min || line->argc > max) { error = err_invalid_argc; return; }
#define HAS(n)					!line->arg##n.is_empty
#define STR(n)					resolve_str(line->arg##n)
#define NUM(n)					resolve_num(line->arg##n)
#define REQUIRE_IDENT(n)		if (!line->arg##n.is_identifier) { error = err_varname_expected; return; }
#define IDENT(n)				line->arg##n.string_val
#define BOOL(n)					NUM(n) > 0

void PTML::set_env(PTM* _ptm, t_screen* _scr) {
	ptm = _ptm; scr = _scr;
}
void PTML::set_line(t_program_line* _line) {
	line = _line;
}
static const t_string& resolve_str(const t_param& arg) {
	return arg.is_identifier ? ptm->get_var_str(arg.string_val) : arg.string_val;
}
static int resolve_num(const t_param& arg) {
	return arg.is_identifier ? ptm->get_var_num(arg.string_val) : arg.numeric_val;
}

//=============================================================================
//									COMMANDS
//=============================================================================

void PTML::COLOR()
{
	ARGC_MIN_MAX(1, 3);

	if (COUNT(3)) {
		if (HAS(1)) scr->color_fg(NUM(1));
		if (HAS(2)) scr->color_bg(NUM(2));
		if (HAS(3)) scr->color_bdr(NUM(3));
	}
	else if (COUNT(2)) {
		if (HAS(1)) scr->color_fg(NUM(1));
		if (HAS(2)) scr->color_bg(NUM(2));
	}
	else if (COUNT(1)) {
		if (HAS(1)) scr->color_fg(NUM(1));
	}
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

	if (IMM)
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

void PTML::FSCR()
{
	ARGC_MIN_MAX(0, 1);

	if (COUNT(1))
		ptm->get_wnd().set_fullscreen(BOOL(1));
	else if (COUNT(0))
		ptm->get_wnd().toggle_fullscreen();
}

void PTML::CSR()
{
	ARGC(1);
	scr->show_cursor(BOOL(1));
}
