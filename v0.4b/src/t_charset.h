#pragma once
#include "t_list.h"
#include "t_binary.h"

class t_charset
{
public:
	t_charset();
	t_charset(const t_charset& other);
	t_charset& operator=(const t_charset& other);

	void remove_all();
	void add(t_binary bits);
	t_binary& get(int index);
	void set(int index, t_binary bits);
	int size() const;
	void reset();

private:
	t_list<t_binary> chars;

	void copy_from(const t_charset& other);
};
