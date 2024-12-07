#include "t_data.h"

t_data::t_data()
{
}

t_data::~t_data()
{
}

t_data::t_data(const t_data& other)
{
    data = other.data;
}

void t_data::clear()
{
    data.clear();
}

void t_data::set(const t_string& key, const t_string& value)
{
    data[key] = value;
}

void t_data::set(const t_string& key, int value)
{
    set(key, t_string::from_int(value));
}

const t_string& t_data::get_str(const t_string& key)
{
    return data[key];
}

const int t_data::get_int(const t_string& key)
{
    return data[key].to_int();
}

bool t_data::has(const t_string& key)
{
    return data.contains(key);
}

bool t_data::has(const t_string& key, const t_string& value)
{
    if (!has(key))
        return false;

    return data[key] == value;
}

const t_dict<t_string, t_string>& t_data::get_all() const
{
    return data;
}

bool t_data::empty() const
{
    return data.empty();
}
