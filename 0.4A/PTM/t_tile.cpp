#include "t_tile.h"
#include "t_ptm.h"
#include "t_image.h"
#include "t_screen.h"

t_tile::t_tile()
{
	set_empty();
}

t_tile::~t_tile()
{
	set_empty();
}

void t_tile::set_image(t_index img_index)
{
	image_index = img_index;
}

t_index t_tile::get_image() const
{
	return image_index;
}

void t_tile::remove_image()
{
	image_index = ptm.invalid_index;
}

bool t_tile::has_image() const
{
	return image_index != ptm.invalid_index;
}

bool t_tile::empty() const
{
	return data.empty() && code.empty() && !has_image();
}

void t_tile::set_empty()
{
	data.clear();
	remove_image();
	reset_flags();
}

void t_tile::reset_flags()
{
	enabled = true;
	visible = true;
	solid = false;
}
