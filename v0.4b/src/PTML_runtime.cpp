#include "PTML_runtime.h"
#include "PTML_macros.h"
#include "PTML_errors.h"
#include "PTM.h"

PTM*			PTML::ptm = nullptr;
t_screen*		PTML::scr = nullptr;
t_program_line* PTML::line = nullptr;
t_string		PTML::error;

void PTML::set_env(PTM* _ptm, t_screen* _scr)
{
	ptm = _ptm;
	scr = _scr;
}

void PTML::set_line(t_program_line* _line)
{
	line = _line;
}

t_string PTML::resolve_str(const t_param& arg)
{
	if (arg.type == t_token_type::invalid)
		return EMPTY_STR;
	if (arg.type == t_token_type::identifier)
		return ptm->has_var(arg.string_val) ? ptm->get_var_str(arg.string_val) : EMPTY_STR;

	return arg.string_val;
}

int PTML::resolve_num(const t_param& arg)
{
	if (arg.type == t_token_type::invalid)
		return EMPTY_NUM;
	if (arg.type == t_token_type::identifier)
		return ptm->has_var(arg.string_val) ? ptm->get_var_num(arg.string_val) : EMPTY_NUM;

	return arg.numeric_val;
}

void PTML::branch_unconditional(t_branch_mode mode)
{
	REQUIRE_NOT_IMM;
	ARGC(1);
	REQUIRE_IDENT(1);

	auto& label = IDENT(1);
	if (ptm->has_program_label(label)) {
		mode == t_branch_mode::go_to ?
			ptm->goto_program_label(label) :
			ptm->call_program_label(label);
	}
	else {
		error = err_label_not_found;
	}
}

void PTML::branch_conditional(t_comparison cp, t_branch_mode mode)
{
	REQUIRE_NOT_IMM;
	ARGC(3);

	auto&& str_a = STR(1);
	auto&& str_b = STR(2);

	bool pass = false;

		 if (cp == t_comparison::eq)	pass = str_a == str_b;
	else if (cp == t_comparison::neq)	pass = str_a != str_b;
	else if (cp == t_comparison::gt)	pass = str_a.to_int() > str_b.to_int();
	else if (cp == t_comparison::gte)	pass = str_a.to_int() >= str_b.to_int();
	else if (cp == t_comparison::lt)	pass = str_a.to_int() < str_b.to_int();
	else if (cp == t_comparison::lte)	pass = str_a.to_int() <= str_b.to_int();

	if (pass) {

		REQUIRE_IDENT(3);
		auto&& label = IDENT(3);
		if (ptm->has_program_label(label)) {
			mode == t_branch_mode::go_to ?
				ptm->goto_program_label(label) :
				ptm->call_program_label(label);
		}
		else {
			error = err_label_not_found;
		}
	}
}
