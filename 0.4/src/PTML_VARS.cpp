#include "PTML_VARS.h"
#include "PTML_shared_headers.h"

void PTML::SET()
{
	ARGC(2);
	ptm->set_var(ARG(1), STR(2), error);
}

void PTML::MEMCLR()
{
	ARGC(0);
	ptm->delete_all_vars();
}

void PTML::DIM()
{
	ARGC(1);
	
	if (!ARG(1).is_array()) {
		error = err.array_expected;
		return;
	}

	ptm->create_array(ARG(1).array_ref, error);
}
