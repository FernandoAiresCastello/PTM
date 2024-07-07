#pragma once
#include <cstdint>

struct t_tileflags
{
	bool visible;
	bool monochrome;
	bool hide_bgc;
	bool line_wrap;

	t_tileflags();
	t_tileflags(const t_tileflags& other);

	bool operator==(const t_tileflags& other) const;
	t_tileflags& operator=(const t_tileflags& other);
	
	void clear();
};
