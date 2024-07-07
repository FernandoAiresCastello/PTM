#include "PTML_INPUT.h"
#include "PTML_shared_headers.h"

void PTML::INKEY()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), ptm->get_last_key());
}

void PTML::KB_FLUSH()
{
	ARGC(0);
	ptm->flush_keyboard();
}
