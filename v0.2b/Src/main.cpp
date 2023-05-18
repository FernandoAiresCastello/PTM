#include "PTM/ptm_core.h"

int main(int argc, char* argv[])
{
	if (argc > 1) {
		return ptm_run(argv[1]);
	}
	return ptm_run("main.ptm");
}
