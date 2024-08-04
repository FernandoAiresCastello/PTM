#include "t_program_runner.h"
#include "PTM.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_interpreter.h"

void t_program_runner::run_program_from_immediate_mode(PTM* ptm, t_program* prg, t_interpreter* intp)
{
	this->ptm = ptm;
	this->prg = prg;
	this->intp = intp;

	do {
		
		cur_line = nullptr;
		stop_requested = false;
		branch_request.active = false;
		branch_request.returning_from_call = false;
		branch_request.target_line = -1;
		new_program_loaded_at_runtime = false;

		clear_callstack();
		find_labels();

		running = true;

		for (auto it = prg->lines.begin(); it != prg->lines.end(); ) {
			cur_line = &it->second;
			auto& line = it->second;
			if (line.is_label || line.is_comment) {
				++it;
				continue;
			}

			bool ok = intp->execute_line(line);
			ptm->on_machine_cycle();
			if (!ok || stop_requested || !ptm->is_window_open())
				break;

			if (branch_request.active) {
				it = prg->lines.find(branch_request.target_line);

				branch_request.active = false;
				branch_request.target_line = -1;

				if (branch_request.returning_from_call) {
					branch_request.returning_from_call = false;
					++it;
				}
			}
			else {
				++it;
			}
		}

		running = false;
	}
	while (new_program_loaded_at_runtime);

	ptm->on_program_end();
}

void t_program_runner::run_program_from_another_program()
{
	stop_requested = true;
	new_program_loaded_at_runtime = true;
}

bool t_program_runner::has_new_program_loaded_at_runtime() const
{
	return new_program_loaded_at_runtime;
}

void t_program_runner::stop()
{
	stop_requested = true;
	new_program_loaded_at_runtime = false;
}

bool t_program_runner::is_running() const
{
	return running;
}

bool t_program_runner::is_stopping() const
{
	return stop_requested;
}

t_program_line* t_program_runner::get_current_line()
{
	return cur_line;
}

void t_program_runner::go_to(int line_nr)
{
	branch_request.active = true;
	branch_request.target_line = line_nr;
}

void t_program_runner::go_to(const t_string& label)
{
	branch_request.active = true;
	branch_request.target_line = labels[label];
}

void t_program_runner::call(const t_string& label)
{
	callstack.push(cur_line->line_nr);
	go_to(label);
}

void t_program_runner::return_from_call()
{
	branch_request.returning_from_call = true;
	int line_to_return = callstack.top();
	callstack.pop();
	go_to(line_to_return);
}

void t_program_runner::find_labels()
{
	labels.clear();

	for (auto& raw_line : prg->lines) {
		auto& line = raw_line.second;
		if (line.is_label) {
			labels[line.label] = line.line_nr;
		}
	}
}

void t_program_runner::clear_callstack()
{
	while (!callstack.empty())
		callstack.pop();
}
