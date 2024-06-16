#pragma once
#include "t_list.h"
#include "t_binary.h"
#include "t_index.h"

class t_charset
{
public:
	t_charset();
	t_charset(const t_charset& other);
	t_charset& operator=(const t_charset& other);

	void remove_all();
	void add(const t_binary& bits);
	t_binary& get(t_index index);
	void set(t_index index, const t_binary& bits);
	int size() const;
	void reset();

private:
	t_list<t_binary> chars;

	void copy_from(const t_charset& other);
};
