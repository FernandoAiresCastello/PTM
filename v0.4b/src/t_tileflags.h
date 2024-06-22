#pragma once
#include <cstdint>

struct t_tileflags
{
	bool visible = true;
	bool monochrome = false;
	bool hide_bgc = false;
	bool line_wrap = false;

	t_tileflags();
	t_tileflags(const t_tileflags& other);

	bool operator==(const t_tileflags& other) const;
	t_tileflags& operator=(const t_tileflags& other);
};
