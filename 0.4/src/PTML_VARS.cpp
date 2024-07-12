#include "PTML_VARS.h"
#include "PTML_shared_headers.h"

void PTML::VAR()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), STR(2));
}

void PTML::VARS()
{
	ARGC(0);
	t_list<t_string> vars;
	for (auto& var : ptm->get_vars())
		vars.push_back(t_string::fmt("%s: %s", var.first.c_str(), var.second.c_str()));
	
	scr->print_lines(vars);
}

void PTML::SWAP()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	REQUIRE_IDENT(2);
	const t_string&& val1 = STR(1);
	const t_string&& val2 = STR(2);
	ptm->set_var(IDENT(1), val2);
	ptm->set_var(IDENT(2), val1);
}

void PTML::VAR_CLR()
{
	ARGC(0);
	ptm->delete_all_vars();
}
