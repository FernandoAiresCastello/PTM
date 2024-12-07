#pragma once
#include "t_string.h"
#include "t_index.h"
#include "t_data.h"

class t_screen;

class t_tile
{
public:
	t_data data;
	t_string code;
	bool enabled = true;
	bool visible = true;
	bool solid = false;

	t_tile();
	~t_tile();

	void set_image(t_index img_index);
	t_index get_image() const;
	void remove_image();
	bool empty() const;
	void set_empty();

private:
	t_index image_index;
};
