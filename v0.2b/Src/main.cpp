#include "PTM/ptm_core.h"
#include "Util/docgen.h"

int main(int argc, char* argv[])
{
	/*
	docgen_main();
	return 0;
	*/

	if (argc > 1) {
		return ptm_run(argv[1]);
	}
	return ptm_run("main.ptm");
}
