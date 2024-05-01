#pragma once
#include "common.h"

struct t_char
{
	int ix = 0;
	int fgc = 0;
	int bgc = 0;

	t_char();
	t_char(int ix, int fgc, int bgc);
	t_char(const t_char& other);

	bool operator==(const t_char& other) const;
	t_char& operator=(const t_char& other);

	void set(int ix, int fgc, int bgc);
	void set_blank();
	bool is_blank() const;
	bool is_not_blank() const;
	static t_char blank();
};
