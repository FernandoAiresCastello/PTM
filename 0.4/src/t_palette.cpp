#include "t_palette.h"
#include "t_filesystem.h"

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

void t_palette::add(const t_color& color)
{
	colors.emplace_back(color);
}

t_color& t_palette::get(t_index index)
{
	return colors[index];
}

void t_palette::set(t_index index, const t_color& color)
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
	t_filesystem::load_default_palette(this);
}

void t_palette::load(const t_string& filename)
{
	remove_all();
	t_filesystem::load_palette_plaintext(this, filename);
}
