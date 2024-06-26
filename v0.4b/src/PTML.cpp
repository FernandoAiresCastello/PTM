#include "PTML.h"
#include "PTM.h"
#include "t_screen.h"
#include "t_program_line.h"

const t_string err_invalid_argc = "Invalid argument count";
const t_string err_varname_expected = "Variable name expected";
const t_string err_undefined_var = "Undefined variable";

#define ARGC(count)				if (line->argc != count) { error = err_invalid_argc; return; }
#define ARGC_MIN_MAX(min, max)	if (line->argc < min || line->argc > max) { error = err_invalid_argc; return; }
#define STR(n)					resolve_str(line->arg##n)
#define NUM(n)					resolve_num(line->arg##n)
#define REQUIRE_IDENT(n)		if (!line->arg##n.is_identifier) { error = err_varname_expected; return; }
#define IDENT(n)				line->arg##n.string_val

PTM* ptm = nullptr;
t_screen* scr = nullptr;
t_program_line* line = nullptr;
t_string PTML::error;

void PTML::set_env(PTM* _ptm, t_screen* _scr)
{
	ptm = _ptm;
	scr = _scr;
}

void PTML::set_line(t_program_line* _line)
{
	line = _line;
}

static const t_string& resolve_str(const t_param& arg) {
	return arg.is_identifier ? ptm->get_var_str(arg.string_val) : arg.string_val;
}
static int resolve_num(const t_param& arg) {
	return arg.is_identifier ? ptm->get_var_num(arg.string_val) : arg.numeric_val;
}

void PTML::COLOR()
{
	ARGC_MIN_MAX(1, 3);

	if (line->argc == 3) {
		scr->color(NUM(1), NUM(2), NUM(3));
	}
	else if (line->argc == 2) {
		scr->color_fg(NUM(1));
		scr->color_bg(NUM(2));
	}
	else if (line->argc == 1) {
		scr->color_fg(NUM(1));
	}
}

void PTML::VARS()
{
	ARGC(0);

	for (auto& var : ptm->get_vars()) {
		scr->println(t_string::fmt("%s: %s", var.first.c_str(), var.second.c_str()));
	}
}

void PTML::PEEK()
{
	ARGC(1);
	REQUIRE_IDENT(1);

	if (ptm->has_var(IDENT(1)))
		scr->println(t_string::fmt("%s: %s", IDENT(1).c_str(), ptm->get_var_str(IDENT(1)).c_str()));
	else
		error = err_undefined_var;
}

void PTML::VAR()
{
	ARGC(2);
	REQUIRE_IDENT(1);

	ptm->set_var(IDENT(1), STR(2));
}

void PTML::EXIT()
{
	ARGC(0);

	ptm->exit();
}
