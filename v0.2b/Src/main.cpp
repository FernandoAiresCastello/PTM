#include "PTM/ptm_core.h"
#include "Util/docgen.h"

#define RUN_DOCGEN 0

int main(int argc, char* argv[])
{
#if RUN_DOCGEN
	docgen_main();
	return 0;
#endif

	if (argc > 1) {
		return ptm_run(argv[1]);
	}
	return ptm_run("main.ptm");
}
