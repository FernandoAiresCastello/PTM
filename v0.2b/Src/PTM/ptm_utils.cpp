#include "ptm_utils.h"

int get_color_r(rgb color)
{
	return (color & 0xff0000) >> 16;
}
int get_color_g(rgb color)
{
	return (color & 0x00ff00) >> 8;
}
int get_color_b(rgb color)
{
	return (color & 0x0000ff);
}
rgb get_color_rgb(int r, int g, int b)
{
	return b | (g << CHAR_BIT) | (r << CHAR_BIT * 2);
}
