#pragma once
#include "t_string.h"
#include "t_dict.h"

class t_data
{
public:
	t_data();
	~t_data();
	t_data(const t_data& other);

	void clear();
	void set(const t_string& key, const t_string& value);
	void set(const t_string& key, int value);
	const t_string& get_str(const t_string& key);
	const int get_int(const t_string& key);
	bool has(const t_string& key);
	bool has(const t_string& key, const t_string& value);
	const t_dict<t_string, t_string>& get_all() const;
	bool empty() const;

private:
	t_dict<t_string, t_string> data;
};
