#include "t_default_gfx.h"
#include "chars.h"

void t_default_gfx::init_palette(TPalette* pal) {
	pal->DeleteAll();
	pal->AddBlank(256);
	// Basic runtime colors
	pal->Set(0, 0x000000); // black
	pal->Set(1, 0xffffff); // white
	/*
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
	pal->Set(245, 0xd00000); // error_bg
	pal->Set(244, 0x0000c0); // pnl_bg
	*/
}
void t_default_gfx::init_charset(TCharset* chr) {
	/*chr->Set(chars::cursor_ovr,
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"11111111"
		"11111111");
	chr->Set(chars::cursor_ins,
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000"
		"11000000");
	chr->Set(chars::horizontal_bar,
		"00000000"
		"00000000"
		"11111111"
		"11111111"
		"00000000"
		"11111111"
		"00000000"
		"00000000");
	chr->Set(chars::file_icon,
		"00000000"
		"01111110"
		"01100010"
		"01110010"
		"01111010"
		"01111110"
		"01111110"
		"00000000");
	*/
	chr->Set(chars::underscore,
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"00000000"
		"01111100"
		"00000000");
	chr->Set(chars::pnl_corner_tl,
		"00000000"
		"00000000"
		"00000000"
		"00011111"
		"00011111"
		"00011000"
		"00011000"
		"00011000");
	chr->Set(chars::pnl_corner_tr,
		"00000000"
		"00000000"
		"00000000"
		"11111000"
		"11111000"
		"00011000"
		"00011000"
		"00011000");
	chr->Set(chars::pnl_corner_bl,
		"00011000"
		"00011000"
		"00011000"
		"00011111"
		"00011111"
		"00000000"
		"00000000"
		"00000000");
	chr->Set(chars::pnl_corner_br,
		"00011000"
		"00011000"
		"00011000"
		"11111000"
		"11111000"
		"00000000"
		"00000000"
		"00000000");
}
