#include "t_ptm.h"
#include "t_tests.h"

t_tests tests;
t_ptm ptm;

int main(int argc, char* argv[])
{
	tests.run();
	ptm.run();

	return 0;
}
