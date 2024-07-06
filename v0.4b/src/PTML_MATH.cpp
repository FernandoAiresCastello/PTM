#include "PTML_MATH.h"
#include "PTML_shared_headers.h"

void PTML::INC()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), ptm->get_var_num(IDENT(1)) + 1);
}

void PTML::DEC()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), ptm->get_var_num(IDENT(1)) - 1);
}

void PTML::ADD()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2))
		ptm->set_var(IDENT(1), NUM(1) + NUM(2));
	else if (COUNT(3))
		ptm->set_var(IDENT(1), NUM(2) + NUM(3));
}

void PTML::SUB()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2))
		ptm->set_var(IDENT(1), NUM(1) - NUM(2));
	else if (COUNT(3))
		ptm->set_var(IDENT(1), NUM(2) - NUM(3));
}

void PTML::MUL()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2))
		ptm->set_var(IDENT(1), NUM(1) * NUM(2));
	else if (COUNT(3))
		ptm->set_var(IDENT(1), NUM(2) * NUM(3));
}

void PTML::DIV()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2)) {
		int divisor = NUM(2);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(1) / divisor);
	}
	else if (COUNT(3)) {
		int divisor = NUM(3);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(2) / divisor);
	}
}

void PTML::DIVR()
{
	ARGC_MIN_MAX(2, 3);
	REQUIRE_IDENT(1);

	if (COUNT(2)) {
		int divisor = NUM(2);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(1) % divisor);
	}
	else if (COUNT(3)) {
		int divisor = NUM(3);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(IDENT(1), NUM(2) % divisor);
	}
}

void PTML::POW()
{
	ARGC(3);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), (int)pow((float)NUM(2), (float)NUM(3)));
}

void PTML::SQRT()
{
	ARGC(2);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), (int)sqrt((float)NUM(2)));
}

void PTML::RND()
{
	ARGC_MIN_MAX(1, 3);
	REQUIRE_IDENT(1);

	if (COUNT(3))
		ptm->set_var(IDENT(1), t_util::rnd(NUM(2), NUM(3)));
	else if (COUNT(2))
		ptm->set_var(IDENT(1), t_util::rnd(NUM(2)));
	else if (COUNT(1))
		ptm->set_var(IDENT(1), t_util::rnd(0, INT_MAX));
}
