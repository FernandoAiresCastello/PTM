#include "PTML_VARS.h"
#include "PTML_shared_headers.h"

void PTML::SET()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), STR(2));
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

void PTML::MEM_CLR()
{
	ARGC(0);
	ptm->delete_all_vars();
}
