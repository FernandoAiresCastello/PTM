#include "t_charset.h"
#include "t_filesystem.h"

t_charset::t_charset()
{
	reset();
}

t_charset::t_charset(const t_charset& other)
{
	copy_from(other);
}

t_charset& t_charset::operator=(const t_charset& other)
{
	if (this == &other)
		return *this;

	copy_from(other);

	return *this;
}

void t_charset::copy_from(const t_charset& other)
{
	remove_all();
	for (int i = 0; i < other.chars.size(); i++) {
		chars.emplace_back(other.chars[i]);
	}
}

void t_charset::remove_all()
{
	chars.clear();
}

void t_charset::add(const t_binary& bits)
{
	chars.emplace_back(bits);
}

t_binary& t_charset::get(t_index index)
{
	return chars[index];
}

void t_charset::set(t_index index, const t_binary& bits)
{
	chars[index] = bits;
}

void t_charset::set_row(t_index chr_index, t_index row, const t_binary& bits)
{
	auto rows = chars[chr_index].split_chunks(8);
	rows[row] = bits.get_first(8);
	chars[chr_index] = t_string::join(rows, "");
}

int t_charset::size() const
{
	return (int)chars.size();
}

void t_charset::reset()
{
	remove_all();
	t_filesystem::load_default_charset(this);
}

void t_charset::load(const t_string& filename)
{
	remove_all();
	t_filesystem::load_charset_plaintext(this, filename);
}

void t_charset::save(const t_string& filename)
{
	t_filesystem::save_charset_plaintext(this, filename);
}
