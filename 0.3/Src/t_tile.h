#pragma once
#include "t_pointers.h"
#include "t_char.h"
#include "t_data.h"
#include "t_tileflags.h"

class t_tile
{
public:
	static constexpr int width = 8;
	static constexpr int height = 8;

	t_data data;
	t_tileflags flags;

	t_tile();
	t_tile(t_index ix, t_index fgc, t_index bgc, t_tileflags flags = t_tileflags());
	t_tile(const t_char& ch);
	t_tile(const t_tile& other);
	explicit t_tile(bool add_blank);
	~t_tile() = default;

	bool operator==(const t_tile& other) const;
	t_tile& operator=(const t_tile& other);

	static t_tile create_blank();

	t_char& get_char();
	t_char& get_char(int position);
	t_char& get_char_wraparound(int position);
	void set_char(t_index ix, t_index fgc, t_index bgc);
	void set_char(int position, t_index ix, t_index fgc, t_index bgc);
	void add_char(t_index ix, t_index fgc, t_index bgc);
	void add_blank_char();
	int char_count() const;
	bool has_any_char() const;
	bool is_blank() const;
	bool is_not_blank() const;
	void set_blank();
	bool is_empty() const;
	bool is_not_empty() const;
	void set_empty();
	t_list<t_char>& get_all_chars();
	void delete_all_chars();

private:
	t_list<t_char> chars;
};
