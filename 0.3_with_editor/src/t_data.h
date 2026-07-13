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
	~t_data() = default;

	bool operator==(const t_data& other) const;
	t_data& operator=(const t_data& other);

	bool is_empty() const;
	bool is_not_empty() const;
	void clear();
	void set(const t_string& key, const t_string& value);
	void set(const t_string& key, int value);
	void remove(const t_string& key);
	t_string get(const t_string& key);
	int get_int(const t_string& key);
	bool has(const t_string& key);
	bool has(const t_string& key, const t_string& value);
	bool has(const t_string& key, int value);
	t_dict<t_string, t_string>& get_all();
	int size() const;

private:
	t_dict<t_string, t_string> entries;
};
