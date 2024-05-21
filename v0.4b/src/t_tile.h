#pragma once
#include "t_char.h"
#include "t_data.h"

class t_tile
{
public:
	static constexpr int width = 8;
	static constexpr int height = 8;

	t_data data;
	int frame_delay = 0;

	t_tile();
	t_tile(int ix, int fgc, int bgc);
	t_tile(const t_tile& other);

	bool operator==(const t_tile& other) const;
	t_tile& operator=(const t_tile& other);

	t_char& get_char();
	t_char& get_char(int index);
	void set_char(int ix, int fgc, int bgc);
	void set_char(int position, int ix, int fgc, int bgc);
	void add_char(int ix, int fgc, int bgc);
	void add_blank_char();
	int char_count();
	bool is_blank() const;
	bool is_not_blank() const;
	void set_blank();
	t_list<t_char>& get_all_chars();

private:
	t_list<t_char> chars;
};
