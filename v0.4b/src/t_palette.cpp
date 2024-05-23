#include "t_palette.h"

t_palette::t_palette()
{
	reset();
}

t_palette::t_palette(const t_palette& other)
{
	copy_from(other);
}

t_palette& t_palette::operator=(const t_palette& other)
{
	if (this == &other)
		return *this;

	copy_from(other);

	return *this;
}

void t_palette::copy_from(const t_palette& other)
{
	remove_all();
	for (int i = 0; i < other.colors.size(); i++) {
		colors.emplace_back(other.colors[i]);
	}
}

void t_palette::remove_all()
{
	colors.clear();
}

void t_palette::add(t_color color)
{
	colors.emplace_back(color);
}

t_color& t_palette::get(int index)
{
	return colors[index];
}

void t_palette::set(int index, t_color color)
{
	colors[index] = color;
}

int t_palette::size() const
{
	return (int)colors.size();
}

void t_palette::reset()
{
	remove_all();

	for (int i = 0; i < 256; i++)
		add(0x000000);

	set(0, 0x101010);
	set(1, 0xe0e0e0);
}
