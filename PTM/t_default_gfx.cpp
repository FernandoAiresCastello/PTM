#include "t_default_gfx.h"

void t_default_gfx::init_palette(TPalette* pal) {
	pal->DeleteAll();
	pal->AddBlank(256);
	pal->Set(0, 0x000000); // black
	pal->Set(1, 0xc0c0c0); // fgcolor
	pal->Set(2, 0x000080); // bgcolor
	pal->Set(3, 0x808080); // bdr_fgcolor
	pal->Set(4, 0x0000c0); // bdr_bgcolor
	pal->Set(5, 0xd0d000); // label_fgcolor
	pal->Set(6, 0x00d0d0); // cmd_fgcolor
	pal->Set(7, 0xffffff); // csr_fgcolor
	pal->Set(8, 0x808080); // comment_fgcolor
}
void t_default_gfx::init_charset(TCharset* chr) {
	// Cursor overwrite
	chr->Set(0xfb, 
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"11111111"
		"11111111");
	// Cursor insert
	chr->Set(0xfc,
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000");
}
