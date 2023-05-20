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
int t_palette::get_r(int index)
{
	return (colors[index] & 0xff0000) >> 16;
}
int t_palette::get_g(int index)
{
	return (colors[index] & 0x00ff00) >> 8;
}
int t_palette::get_b(int index)
{
	return (colors[index] & 0x0000ff);
}
void t_palette::set_r(int index, int value)
{
	colors[index] &= 0x00ffff;
	colors[index] |= (value << 16);
}
void t_palette::set_g(int index, int value)
{
	colors[index] &= 0xff00ff;
	colors[index] |= (value << 8);
}
void t_palette::set_b(int index, int value)
{
	colors[index] &= 0xffff00;
	colors[index] |= value;
}
