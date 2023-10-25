#include "PTM/ptm_core.h"
#include "PTM/ptm_filesystem.h"
#include "System/ptm_system.h"

int main(int argc, char* argv[])
{
	ptm_system* sys = new ptm_system();
	sys->run();
	return 0;

	/*
	if (argc > 1) {
		return ptm_run(argv[1]);
	}
	string main_file = ptm_get_filesys_path("main.ptm");
	return ptm_run(main_file);
	*/
}
