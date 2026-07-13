#include "PTML_INPUT.h"
#include "PTML_shared_headers.h"

void PTML::INKEY()
{
	ARGC(1);
	ptm->set_var(ARG(1), ptm->get_last_key(), error);
}

void PTML::KB_FLUSH()
{
	ARGC(0);
	ptm->flush_keyboard();
}

void PTML::INPUT()
{
	ARGC_MIN_MAX(1, 3);
	auto&& var = ARG(1);
	auto&& default_value = line->argc > 1 ? STR(2) : "";
	auto&& maxlen = line->argc > 2 ? NUM(3) : 255;

	t_string value = ptm->input_string("", default_value, maxlen);
	ptm->set_var(var, value, error);
}
