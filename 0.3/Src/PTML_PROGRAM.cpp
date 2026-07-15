#include "PTML_PROGRAM.h"
#include "PTML_shared_headers.h"

void PTML::RUN()
{
	ARGC_MIN_MAX(0, 1);

	if (COUNT(0)) {
		ptm->run_program_from_another_program();
	}
	if (COUNT(1)) {
		if (!try_load_program(STR(1)))
			return;

		ptm->run_program_from_another_program();
	}
}

void PTML::TITLE()
{
	ARGC(1);
	ptm->get_wnd().set_title(STR(1));
}
