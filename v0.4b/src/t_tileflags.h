#pragma once
#include <cstdint>

struct t_tileflags
{
	bool visible = true;
	bool monochrome = false;
	bool hide_bgc = false;

	t_tileflags();

	bool operator==(const t_tileflags& other) const;
};
