#include "PTML_VARS.h"
#include "PTML_shared_headers.h"

void PTML::SET()
{
	ARGC(2);
	ptm->set_var(ARG(1), STR(2), error);
}

void PTML::ARR_LEN()
{
	ARGC(2);
	ptm->set_var(ARG(1), ptm->get_array_length(IDENT(2), error), error);
}

void PTML::SWAP()
{
	ARGC(2);
	
	auto&& left = STR(1);
	auto&& right = STR(2);

	ptm->set_var(ARG(1), right, error);
	if (error.empty())
		ptm->set_var(ARG(2), left, error);
}

void PTML::ARR_DIM()
{
	ARGC(1);
	if (!ARG(1).is_array()) {
		error = err.array_expected;
		return;
	}
	ptm->create_array(ARG(1).array_ref, error);
}

void PTML::MEMCLR()
{
	ARGC(0);
	ptm->delete_all_vars();
}

void PTML::STR_CONCAT()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(2))
		ptm->set_var(ARG(1), STR(1) + STR(2), error);
	else if (COUNT(3))
		ptm->set_var(ARG(1), STR(2) + STR(3), error);
}

void PTML::STR_UPPER()
{
	ARGC_MIN_MAX(1, 2);

	if (COUNT(1))
		ptm->set_var(ARG(1), STR(1).to_upper(), error);
	else if (COUNT(2))
		ptm->set_var(ARG(1), STR(2).to_upper(), error);
}

void PTML::STR_LOWER()
{
	ARGC_MIN_MAX(1, 2);

	if (COUNT(1))
		ptm->set_var(ARG(1), STR(1).to_lower(), error);
	else if (COUNT(2))
		ptm->set_var(ARG(1), STR(2).to_lower(), error);
}

void PTML::STR_FIND()
{
	ARGC(3);
	auto&& index = STR(2).index_of(STR(3));
	ptm->set_var(ARG(1), index >= 0 ? index : -1, error);
}

void PTML::STR_SUBSTR()
{
	ARGC_MIN_MAX(3, 4);
	if (COUNT(3)) {
		auto&& substr = STR(2).substr(NUM(3));
		ptm->set_var(ARG(1), substr, error);
	}
	else if (COUNT(4)) {
		auto&& substr = STR(2).substr(NUM(3), NUM(4));
		ptm->set_var(ARG(1), substr, error);
	}
}

void PTML::STR_LEN()
{
	ARGC(2);
	ptm->set_var(ARG(1), STR(2).length(), error);
}

void PTML::STR_ASCII()
{
	ARGC(2);
	if (ARG(2).type == t_token_type::literal_char)
		ptm->set_var(ARG(1), ARG(2).numeric_val, error);
	else if (ARG(2).type == t_token_type::literal_str && ARG(2).string_val.length() >= 1)
		ptm->set_var(ARG(1), ARG(2).string_val[0], error);
	else if (ARG(2).type == t_token_type::literal_num)
		error = err.illegal_argument;
	else
		ptm->set_var(ARG(1), STR(2)[0], error);
}

void PTML::STR_CHAR()
{
	ARGC(3);

	auto&& str = STR(2);
	auto&& index = NUM(3);
	if (index < 0 || index >= str.length()) {
		error = err.arg_out_of_range;
		return;
	}
	ptm->set_var(ARG(1), t_string(str[index]), error);
}
