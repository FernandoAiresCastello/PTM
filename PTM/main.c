#include "ptm.h"

int main(int argc, char* argv[])
{
	ptm_init("test_programs/Invaders.ptm");
	int ixcol = 0;

	while (true) {
		if (ixcol == 0)
			ptm_wnd_bgcol(0x808080);
		else
			ptm_wnd_bgcol(0x707070);

		ptm_clear_screen();
		ptm_update();

		ixcol++;
		if (ixcol > 1)
			ixcol = 0;
	}

	return 0;
}
