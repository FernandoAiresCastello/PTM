#include "t_tile.h"

t_tile::t_tile()
{
	add_blank_char();
}

t_tile::t_tile(int ix, int fgc, int bgc)
{
	chars.emplace_back(ix, fgc, bgc);
}

t_tile::t_tile(const t_tile& other)
{
	chars = other.chars;
}

bool t_tile::operator==(const t_tile& other) const
{
	if (chars.size() != other.chars.size())
		return false;

	bool chars_equal = std::equal(chars.begin(), chars.end(), other.chars.begin());
	bool data_equal = data == other.data;

	return chars_equal && data_equal;
}

t_tile& t_tile::operator=(const t_tile& other)
{
	if (this == &other)
		return *this;

	chars = other.chars;
	data = other.data;

	return *this;
}

t_char& t_tile::get_char()
{
	return chars[0];
}

t_char& t_tile::get_char(int index)
{
	return chars[index];
}

void t_tile::set_char(int ix, int fgc, int bgc)
{
	chars[0].set(ix, fgc, bgc);
}

void t_tile::set_char(int ch_ix, int ix, int fgc, int bgc)
{
	chars[ch_ix].set(ix, fgc, bgc);
}

void t_tile::add_char(int ix, int fgc, int bgc)
{
	chars.emplace_back(ix, fgc, bgc);
}

int t_tile::char_count()
{
	return (int)chars.size();
}

void t_tile::set_blank()
{
	chars.clear();
	chars.emplace_back(t_char::blank());

	data.clear();
}

void t_tile::add_blank_char()
{
	chars.emplace_back(t_char::blank());
}

bool t_tile::is_blank() const
{
	return chars.size() == 1 && chars[0].is_blank() && data.is_empty();
}

bool t_tile::is_not_blank() const
{
	return !is_blank();
}
