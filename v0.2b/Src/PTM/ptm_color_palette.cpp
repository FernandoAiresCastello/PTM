#include "ptm_color_palette.h"
#include "ptm_filesystem.h"
#include "ptm_core.h"

t_palette palette;

t_palette::t_palette()
{
	reset();
}
void t_palette::reset()
{
	colors.clear();
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
int ptm_rgb_extract_r(rgb color)
{
	return (color & 0xff0000) >> 16;
}
int ptm_rgb_extract_g(rgb color)
{
	return (color & 0x00ff00) >> 8;
}
int ptm_rgb_extract_b(rgb color)
{
	return (color & 0x0000ff);
}
rgb ptm_rgb_from_components(int r, int g, int b)
{
	return b | (g << CHAR_BIT) | (r << CHAR_BIT * 2);
}
void ptm_save_palette(string file)
{
	vector<string> colors;
	for (rgb& color : palette.colors) {
		colors.push_back(String::Format("%06X", color));
	}
	File::WriteLines(file, colors, "\n");
}
void ptm_load_palette(string file)
{
	ptm_assert_file_exists(file);
	palette.reset();
	auto colors = File::ReadLines(file, "\n");
	if (colors.size() > 256) {
		ptm_abort("Cannot load more than 256 colors in the palette");
	}
	int index = 0;
	for (string& color_str : colors) {
		rgb color = String::ToInt("0x" + color_str);
		palette.set(index, color);
		index++;
	}
}
