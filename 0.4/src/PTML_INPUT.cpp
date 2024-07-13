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

void PTML::FN_SET()
{
	REQUIRE_IMM;
	ARGC(2);
	auto&& keyname = STR(1);
	auto&& value = STR(2);

	bool valid = keyname.has_length(2, 3) && 
		(keyname.starts_with("F") || keyname.starts_with("f") || 
		 keyname.starts_with("S") || keyname.starts_with("s"));

	if (!valid || !ptm->set_function_key(keyname, value))
		error = err.unknown_fn_keyname;
}

void PTML::FN_LIST()
{
	REQUIRE_IMM;
	ARGC(0);
	PRINT_LIST(ptm->list_function_keys());
}
