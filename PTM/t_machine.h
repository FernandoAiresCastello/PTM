#pragma once
#include "common.h"

struct t_machine {
	t_machine();
	~t_machine();

	int memory[MEMORY_TOP] = { 0 };

	void clear_memory();
	int peek(int addr);
	void poke(int addr, int value);
	void update_window(TBufferedWindow* wnd);
};
