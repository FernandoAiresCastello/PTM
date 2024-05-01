#include "t_data.h"

t_data::t_data()
{
}

t_data::t_data(const t_data& other)
{
	entries = other.entries;
}

bool t_data::operator==(const t_data& other) const
{
	if (entries.size() != other.entries.size())
		return false;

	return std::equal(entries.begin(), entries.end(), other.entries.begin());
}

t_data& t_data::operator=(const t_data& other)
{
	if (this == &other)
		return *this;

	entries = other.entries;

	return *this;
}

bool t_data::is_empty() const
{
	return entries.empty();
}

bool t_data::is_not_empty() const
{
	return !is_empty();
}

void t_data::clear()
{
	entries.clear();
}

void t_data::set(std::string key, std::string value)
{
	entries[key] = value;
}

void t_data::set(std::string key, int value)
{
	entries[key] = std::to_string(value);
}

std::optional<std::string> t_data::get(std::string key)
{
	return has(key) ? std::make_optional(entries[key]) : std::nullopt;
}

std::optional<int> t_data::get_int(std::string key)
{
	return has(key) ? std::make_optional(std::stoi(entries[key])) : std::nullopt;
}

bool t_data::has(std::string key)
{
	return entries.contains(key);
}

bool t_data::has(std::string key, std::string value)
{
	return has(key) && entries[key] == value;
}

bool t_data::has(std::string key, int value)
{
	return has(key) && std::stoi(entries[key]) == value;
}

std::unordered_map<std::string, std::string> t_data::get_all()
{
	return entries;
}
