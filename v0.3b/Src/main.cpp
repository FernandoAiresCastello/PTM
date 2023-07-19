#include "PTM/ptm_core.h"
#include "PTM/ptm_filesystem.h"
#include "Editor/ptm_editor.h"
#include "Docgen/docgen.h"

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
	string main_file = ptm_get_filesys_path("main.ptm");
	return ptm_run(main_file);
	//return ptm_edit();
}
