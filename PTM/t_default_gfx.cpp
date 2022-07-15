#include "t_default_gfx.h"

void t_default_gfx::init_palette(TPalette* pal) {
	pal->DeleteAll();
	pal->AddBlank(256);
	// Runtime colors
	pal->Set(0, 0x000000); // black
	pal->Set(1, 0xffffff); // white
	// Program editor colors
	pal->Set(255, 0xc0c0c0); // fgcolor
	pal->Set(254, 0x000080); // bgcolor
	pal->Set(253, 0x808080); // bdr_fgcolor
	pal->Set(252, 0x0000c0); // bdr_bgcolor
	pal->Set(251, 0xd0d000); // label_fgcolor
	pal->Set(250, 0x00d0d0); // cmd_fgcolor
	pal->Set(249, 0xffffff); // csr_fgcolor
	pal->Set(248, 0x808080); // comment_fgcolor
	pal->Set(247, 0x0000ff); // sel_bgcolor
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
