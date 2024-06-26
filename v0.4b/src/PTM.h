#pragma once
#include "t_string.h"
#include "t_list.h"
#include "t_dict.h"
#include "t_token.h"

class PTM
{
public:
	const t_string title = "PTM - Programmable Tile Machine";

	void run();
	void exit();
	void halt();
	void pause(int frames);
	void debug(t_string msg);
	void save_program_line(const t_list<t_token>& tokens);
	void set_var(const t_string& var, const t_string& value);
	void set_var(const t_string& var, int value);
	const t_string& get_var_str(const t_string& var);
	int get_var_num(const t_string& var);
	const t_dict<t_string, t_string>& get_vars();
	bool has_var(const t_string& var);

private:
	bool running = false;
	t_dict<t_string, t_string> vars;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();
	void on_machine_cycle();
};
