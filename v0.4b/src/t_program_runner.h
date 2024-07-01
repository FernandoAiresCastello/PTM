#pragma once
#include "t_dict.h"
#include "t_string.h"
#include "t_program_line.h"

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
	t_program_line* get_current_line();
	void go_to(const t_string& label);
	void call(const t_string& label);

private:
	PTM* ptm = nullptr;
	t_program* prg = nullptr;
	t_interpreter* intp = nullptr;
	t_program_line* cur_line = nullptr;
	bool running = false;
	bool stop_requested = false;
	bool branch_requested = false;
	int branch_target = -1;

	void find_labels();
};
