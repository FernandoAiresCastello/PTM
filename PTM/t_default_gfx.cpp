#include "t_default_gfx.h"
#include "chars.h"

void t_default_gfx::init_palette(TPalette* pal) {
	//pal->DeleteAll();
	//pal->AddBlank(256);
	//pal->Set(0, 0x000000); // black
	//pal->Set(1, 0xffffff); // white
}
void t_default_gfx::init_charset(TCharset* chr) {
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
