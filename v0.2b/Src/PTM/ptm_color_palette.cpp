#include "ptm_color_palette.h"

t_palette palette;

t_palette::t_palette()
{
	add_blank(256);
	set(0, 0x101010);
	set(1, 0xf0f0f0);
}
void t_palette::add_blank(int count)
{
	for (int i = 0; i < count; i++) {
		colors.push_back(0x000000);
	}
}
void t_palette::add(rgb color)
{
	colors.push_back(color);
}
void t_palette::set(int index, rgb color)
{
	colors[index] = color;
}
rgb& t_palette::get(int index)
{
	return colors[index];
}
