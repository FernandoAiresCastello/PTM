#include "t_default_gfx.h"

void t_default_gfx::init_palette(TPalette* pal) {
	pal->DeleteAll();
	pal->AddBlank(256);
	// Runtime colors
	pal->Set(0, 0x000000); // black
	pal->Set(1, 0xffffff); // white
	// Program editor colors
	pal->Set(255, 0xc0c0c0); // fg
	pal->Set(254, 0x000080); // bg
	pal->Set(253, 0x6060c0); // bdr_fg
	pal->Set(252, 0x0000c0); // bdr_bg
	pal->Set(251, 0xd0d000); // label_fg
	pal->Set(250, 0x00d0d0); // cmd_fg
	pal->Set(249, 0xffffff); // csr_fg
	pal->Set(248, 0x808080); // comment_fg
	pal->Set(247, 0x0000ff); // sel_bg
	pal->Set(246, 0xffffff); // fg_bold
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
	// Underscore
	chr->Set('_',
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"01111100"
		"00000000");
	// Horizontal bar
	chr->Set('~',
		"00000000"
		"00000000"
		"00000000"
		"11111111"
		"11111111"
		"00000000"
		"00000000"
		"00000000");
	// Panel TL corner
	chr->Set(0xda,
		"00000000"
		"00000000"
		"00000000"
		"00011111"
		"00011111"
		"00011000"
		"00011000"
		"00011000");
	// Panel TR corner
	chr->Set(0xbf,
		"00000000"
		"00000000"
		"00000000"
		"11111000"
		"11111000"
		"00011000"
		"00011000"
		"00011000");
	// Panel BL corner
	chr->Set(0xc0,
		"00011000"
		"00011000"
		"00011000"
		"00011111"
		"00011111"
		"00000000"
		"00000000"
		"00000000");
	// Panel BR corner
	chr->Set(0xd9,
		"00011000"
		"00011000"
		"00011000"
		"11111000"
		"11111000"
		"00000000"
		"00000000"
		"00000000");
}
