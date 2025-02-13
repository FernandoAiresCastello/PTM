#include "PTML_CTFLOW.h"
#include "PTML_shared_headers.h"

void PTML::END()
{
	ARGC(0);
	ptm->end_program();
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

void PTML::RESET()
{
	ARGC(0);
	ptm->reset();
}

void PTML::GOTO()
{
	branch_unconditional(t_branch_mode::go_to);
}

void PTML::GOTO_IFE()
{
	branch_conditional(t_comparison::eq, t_branch_mode::go_to);
}

void PTML::GOTO_IFNE()
{
	branch_conditional(t_comparison::neq, t_branch_mode::go_to);
}

void PTML::GOTO_IFG()
{
	branch_conditional(t_comparison::gt, t_branch_mode::go_to);
}

void PTML::GOTO_IFGE()
{
	branch_conditional(t_comparison::gte, t_branch_mode::go_to);
}

void PTML::GOTO_IFL()
{
	branch_conditional(t_comparison::lt, t_branch_mode::go_to);
}

void PTML::GOTO_IFLE()
{
	branch_conditional(t_comparison::lte, t_branch_mode::go_to);
}

void PTML::GOTO_IFKEY()
{
	branch_if_keypress(t_branch_mode::go_to, true);
}

void PTML::GOTO_IFNKEY()
{
	branch_if_keypress(t_branch_mode::go_to, false);
}

void PTML::CALL()
{
	branch_unconditional(t_branch_mode::call);
}

void PTML::CALL_IFE()
{
	branch_conditional(t_comparison::eq, t_branch_mode::call);
}

void PTML::CALL_IFNE()
{
	branch_conditional(t_comparison::neq, t_branch_mode::call);
}

void PTML::CALL_IFG()
{
	branch_conditional(t_comparison::gt, t_branch_mode::call);
}

void PTML::CALL_IFGE()
{
	branch_conditional(t_comparison::gte, t_branch_mode::call);
}

void PTML::CALL_IFL()
{
	branch_conditional(t_comparison::lt, t_branch_mode::call);
}

void PTML::CALL_IFLE()
{
	branch_conditional(t_comparison::lte, t_branch_mode::call);
}

void PTML::CALL_IFKEY()
{
	branch_if_keypress(t_branch_mode::call, true);
}

void PTML::CALL_IFNKEY()
{
	branch_if_keypress(t_branch_mode::call, false);
}

void PTML::RET()
{
	ARGC(0);
	if (ptm->is_callstack_empty())
		error = "Call stack empty";
	else
		ptm->return_from_call();
}

void PTML::PAUSE()
{
	ARGC(1);
	ptm->pause(NUM(1));
}

void PTML::BREAK()
{
	ARGC(1);
	ptm->enable_user_break = BOOL(1);
}

void PTML::HCF()
{
	ARGC(0);
	ptm->halt_and_catch_fire();
}
