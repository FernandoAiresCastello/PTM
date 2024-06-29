#include "t_program_runner.h"
#include "PTM.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_interpreter.h"

void t_program_runner::run(PTM* ptm, t_program* prg, t_interpreter* intp)
{
	this->ptm = ptm;
	this->prg = prg;
	this->intp = intp;

	stop_requested = false;
	branch_requested = false;
	branch_target = -1;
	cur_line = nullptr;

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

		if (branch_requested) {
			it = prg->lines.find(branch_target);
			branch_requested = false;
			branch_target = -1;
		}
		else {
			++it;
		}
	}

	running = false;
}

void t_program_runner::stop()
{
	stop_requested = true;
}

bool t_program_runner::is_running() const
{
	return running;
}

t_program_line* t_program_runner::get_current_line()
{
	return cur_line;
}

void t_program_runner::go_to(const t_string& label)
{
	branch_requested = true;
	branch_target = labels[label];
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
