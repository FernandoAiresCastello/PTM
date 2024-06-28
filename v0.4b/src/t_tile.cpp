#include "t_tile.h"

t_tile::t_tile()
{
	add_blank_char();
}

t_tile::t_tile(t_index ix, t_index fgc, t_index bgc, t_tileflags flags) : flags(flags)
{
	chars.emplace_back(ix, fgc, bgc);
}

t_tile::t_tile(const t_tile& other) : chars(other.chars), data(other.data), flags(other.flags)
{
}

bool t_tile::operator==(const t_tile& other) const
{
	if (chars.size() != other.chars.size())
		return false;

	bool chars_equal = std::equal(chars.begin(), chars.end(), other.chars.begin());
	bool data_equal = data == other.data;
	bool flags_equal = flags == other.flags;

	return chars_equal && data_equal && flags_equal;
}

t_tile& t_tile::operator=(const t_tile& other)
{
	if (this == &other)
		return *this;

	chars = other.chars;
	data = other.data;
	flags = other.flags;

	return *this;
}

t_char& t_tile::get_char()
{
	return chars[0];
}

t_char& t_tile::get_char(int position)
{
	return chars[position];
}

t_char& t_tile::get_char_wraparound(int position)
{
	return chars[position % chars.size()];
}

void t_tile::set_char(t_index ix, t_index fgc, t_index bgc)
{
	chars[0].set(ix, fgc, bgc);
}

void t_tile::set_char(int position, t_index ix, t_index fgc, t_index bgc)
{
	chars[position].set(ix, fgc, bgc);
}

void t_tile::add_char(t_index ix, t_index fgc, t_index bgc)
{
	chars.emplace_back(ix, fgc, bgc);
}

void t_tile::add_blank_char()
{
	chars.emplace_back(t_char::blank());
}

int t_tile::char_count()
{
	return (int)chars.size();
}

bool t_tile::has_any_char()
{
	return !chars.empty();
}

bool t_tile::is_blank() const
{
	return chars.size() == 1 && chars[0].is_blank() && data.is_empty();
}

bool t_tile::is_not_blank() const
{
	return !is_blank();
}

void t_tile::set_blank()
{
	set_empty();
	chars.emplace_back(t_char::blank());
}

bool t_tile::is_empty() const
{
	return chars.empty() && data.is_empty();
}

bool t_tile::is_not_empty() const
{
	return !is_empty();
}

void t_tile::set_empty()
{
	chars.clear();
	data.clear();
}

t_list<t_char>& t_tile::get_all_chars()
{
	return chars;
}
