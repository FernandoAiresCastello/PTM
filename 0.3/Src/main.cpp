#include <SDL.h>
#include "PTM.h"

PTM ptm;

int main(int argc, char* argv[])
{
	if (argc >= 2)
		ptm.run(argv[1]);
	else
		ptm.run(nullptr);

	return 0;
}
