#include "PTM/ptm_core.h"
#include "PTM/ptm_filesystem.h"
#include "System/ptm_system.h"

int main(int argc, char* argv[])
{
	ptm_system* sys = new ptm_system();
	sys->run();
	return 0;
}
