#pragma once
#include "t_dict.h"
#include "t_string.h"

class t_program;
class t_interpreter;

class t_program_runner
{
public:
	void run(t_program* prg, t_interpreter* intp);
	void stop();

private:
	t_program* prg = nullptr;
	t_interpreter* intp = nullptr;
	t_dict<t_string, int> labels;
	bool stop_requested = false;
	bool branch_requested = false;
	int branch_target = -1;

	void find_labels();
};
