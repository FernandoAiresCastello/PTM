#pragma once
#include "t_string.h"
#include "t_list.h"
#include "t_token.h"

class PTM
{
public:
	const t_string title = "PTM - Programmable Tile Machine";

	void run();
	void halt();
	void pause(int frames);
	void debug(t_string msg);
	void save_program_line(const t_list<t_token>& tokens);

private:
	bool running = false;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();
	void on_machine_cycle();
};
