#pragma once

struct t_tileflags
{
	// All monochrome tiles on the screen share the same fore and back colors as the screen itself
	// This means changing the colors of the screen will automatically change all monochrome tiles to match those colors
	bool monochrome = false;
};
