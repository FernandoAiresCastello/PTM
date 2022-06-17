#pragma once
#include "common.h"
#include "t_param.h"

struct t_interpreter;
struct t_machine;

struct t_command {
	t_command(t_interpreter* intp);
	bool execute(string& cmd, t_params& args);
private:
	t_interpreter* intp;
	t_machine* machine;
	void save_memory_dump(t_params& arg);
	void halt(t_params& arg);
	void exit(t_params& arg);
	void branch(t_params& arg);
	void define_alias(t_params& arg);
	void poke(t_params& arg);
	void poke_string(t_params& arg);
	void add_to_memory_value(t_params& arg);
	void increment_memory_value(t_params& arg);
	void increment_alias_address(t_params& arg);
	void decrement_alias_address(t_params& arg);
};
