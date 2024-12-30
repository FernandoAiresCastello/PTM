#pragma once
#include "t_list.h"
#include "t_color.h"
#include "t_index.h"
#include "t_string.h"

class t_palette
{
public:
	t_palette();
	t_palette(const t_palette& other);
	t_palette& operator=(const t_palette& other);

	void remove_all();
	void add(const t_color& color);
	t_color& get(t_index index);
	void set(t_index index, const t_color& color);
	int size() const;
	void reset();
	void load(const t_string& filename);

private:
	t_list<t_color> colors;

	void copy_from(const t_palette& other);
};
