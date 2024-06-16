#pragma once
#include "t_index.h"

class t_char
{
public:
	t_index ix = 0;
	t_index fgc = 0;
	t_index bgc = 0;

	t_char();
	t_char(t_index ix, t_index fgc, t_index bgc);
	t_char(const t_char& other);

	bool operator==(const t_char& other) const;
	t_char& operator=(const t_char& other);

	void set(t_index ix, t_index fgc, t_index bgc);
	void set_blank();
	bool is_blank() const;
	bool is_not_blank() const;
	static t_char blank();
};
