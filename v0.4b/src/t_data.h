#pragma once
#include "t_dict.h"
#include "t_string.h"

class t_data
{
public:
	static const t_string null;
	static const int null_int;

	t_data();
	t_data(const t_data& other);
	~t_data();

	bool operator==(const t_data& other) const;
	t_data& operator=(const t_data& other);

	bool is_empty() const;
	bool is_not_empty() const;
	void clear();
	void set(t_string key, t_string value);
	void set(t_string key, int value);
	void remove(t_string key);
	t_string get(t_string key);
	int get_int(t_string key);
	bool has(t_string key);
	bool has(t_string key, t_string value);
	bool has(t_string key, int value);
	t_dict<t_string, t_string>& get_all();

private:
	t_dict<t_string, t_string> entries;
};
