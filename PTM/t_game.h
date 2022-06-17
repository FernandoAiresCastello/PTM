#pragma once
#include "common.h"

struct t_game {
	t_game();
	std::map<string, int> address_alias;
	bool has_address_alias(string alias);
	int get_address_with_alias(string alias);
	int peek_address(int address);
	int peek_address_with_alias(string alias);
	void poke_address(int address, int value);
	void poke_address_with_alias(string alias, int value);
	void clear_memory();
	string get_string_from_address_with_alias(string alias);
	string get_string_from_address(int start_address);

	int bgcolor = 0;
	struct {
		int fg = 15;
		int bg = 0;
		int x = 0;
		int y = 0;
		int layer = 0;
	} text;

private:
	int memory[MEMORY_TOP];
};
