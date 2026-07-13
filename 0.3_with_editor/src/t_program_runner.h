#pragma once
#include "t_program_line.h"
#include "t_string.h"
#include "t_dict.h"
#include "t_stack.h"

class PTM;
class t_program;
class t_interpreter;

class t_program_runner
{
public:
	t_dict<t_string, int> labels;
	t_stack<int> callstack;

	void run_program_from_immediate_mode(PTM* ptm, t_program* prg, t_interpreter* intp);
	void run_program_from_another_program();
	bool has_new_program_loaded_at_runtime() const;
	void stop();
	bool is_running() const;
	bool is_stopping() const;
	t_program_line* get_current_line();
	void go_to(int line_nr);
	void go_to(const t_string& label);
	void call(const t_string& label);
	void return_from_call();

private:
	PTM* ptm = nullptr;
	t_program* prg = nullptr;
	t_interpreter* intp = nullptr;
	t_program_line* cur_line = nullptr;
	bool running = false;
	bool stop_requested = false;
	bool new_program_loaded_at_runtime = false;
	
	struct {
		bool active = false;
		bool returning_from_call = false;
		int target_line = -1;
	} branch_request;

	void find_labels();
	void clear_callstack();
};
