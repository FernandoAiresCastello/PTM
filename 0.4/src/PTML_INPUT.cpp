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

void PTML::INPUT()
{
	ARGC_MIN_MAX(1, 2);
	REQUIRE_IDENT(1);
	
	t_string value;
	if (COUNT(1))
		value = ptm->input_string("", 255);
	else if (COUNT(2))
		value = ptm->input_string("", NUM(2));

	ptm->set_var(IDENT(1), value);
}
