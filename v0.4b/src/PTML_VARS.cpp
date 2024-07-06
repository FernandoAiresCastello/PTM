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
	for (auto& var : ptm->get_vars()) {
		scr->println(t_string::fmt("%s: %s", var.first.c_str(), var.second.c_str()));
	}
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
