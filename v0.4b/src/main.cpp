#include "t_ptm.h"
#include "t_tests.h"

t_ptm ptm;
t_tests tests;

int main(int argc, char* argv[])
{
	tests.run();
	ptm.run();

	return 0;
}
