#pragma once
#include "common.h"

struct t_machine {
	static const int illegal_address = -1;
	static const int memory_top = 0x10000;
	static const int scrbuf_cols = 32;
	static const int scrbuf_rows = 24;

	std::vector<int> memory;
	std::map<string, int> mmap;
	t_machine();
	~t_machine();
	void clear_memory();
	void init_memory_map();
	int peek(int addr);
	int peek(string alias);
	void poke(int addr, int value);
	void poke(string alias, int value);
	void update_window(TBufferedWindow* wnd);
};
