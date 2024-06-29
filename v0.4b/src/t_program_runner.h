#pragma once
#include "t_dict.h"
#include "t_string.h"

class PTM;
class t_program;
class t_interpreter;

class t_program_runner
{
public:
	t_dict<t_string, int> labels;

	void run(PTM* ptm, t_program* prg, t_interpreter* intp);
	void stop();
	bool is_running() const;
	void go_to(const t_string& label);

private:
	PTM* ptm = nullptr;
	t_program* prg = nullptr;
	t_interpreter* intp = nullptr;
	bool running = false;
	bool stop_requested = false;
	bool branch_requested = false;
	int branch_target = -1;

	void find_labels();
};
