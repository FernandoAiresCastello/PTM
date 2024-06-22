#pragma once
#include <SDL.h>
#include "t_string.h"

class PTM
{
public:
	const t_string title = "PTM - Programmable Tile Machine";

	void run();
	void halt();
	void pause(int frames);
	void debug(t_string msg);

private:
	bool running = false;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();
	void on_machine_cycle();
};
