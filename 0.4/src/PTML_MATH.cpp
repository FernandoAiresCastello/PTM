#include "PTML_MATH.h"
#include "PTML_shared_headers.h"

void PTML::INC()
{
	ARGC(1);
	ptm->set_var(ARG(1), NUM(1) + 1, error);
}

void PTML::DEC()
{
	ARGC(1);
	ptm->set_var(ARG(1), NUM(1) - 1, error);
}

void PTML::ADD()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(2))
		ptm->set_var(ARG(1), NUM(1) + NUM(2), error);
	else if (COUNT(3))
		ptm->set_var(ARG(1), NUM(2) + NUM(3), error);
}

void PTML::SUB()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(2))
		ptm->set_var(ARG(1), NUM(1) - NUM(2), error);
	else if (COUNT(3))
		ptm->set_var(ARG(1), NUM(2) - NUM(3), error);
}

void PTML::MUL()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(2))
		ptm->set_var(ARG(1), NUM(1) * NUM(2), error);
	else if (COUNT(3))
		ptm->set_var(ARG(1), NUM(2) * NUM(3), error);
}

void PTML::DIV()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(2)) {
		int divisor = NUM(2);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(ARG(1), NUM(1) / divisor, error);
	}
	else if (COUNT(3)) {
		int divisor = NUM(3);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(ARG(1), NUM(2) / divisor, error);
	}
}

void PTML::DIVR()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(2)) {
		int divisor = NUM(2);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(ARG(1), NUM(1) % divisor, error);
	}
	else if (COUNT(3)) {
		int divisor = NUM(3);
		if (divisor == 0)
			error = err.division_by_zero;
		else
			ptm->set_var(ARG(1), NUM(1) % divisor, error);
	}
}

void PTML::POW()
{
	ARGC(3);
	ptm->set_var(ARG(1), (int)pow((float)NUM(2), (float)NUM(3)), error);
}

void PTML::SQRT()
{
	ARGC(2);
	ptm->set_var(ARG(1), (int)sqrt((float)NUM(2)), error);
}

void PTML::RND()
{
	ARGC_MIN_MAX(2, 3);

	if (COUNT(3))
		ptm->set_var(ARG(1), t_util::rnd(NUM(2), NUM(3)), error);
	else if (COUNT(2))
		ptm->set_var(ARG(1), t_util::rnd(NUM(2)), error);
}
