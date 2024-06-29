#include "t_program_runner.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_interpreter.h"

void t_program_runner::run(t_program* prg, t_interpreter* intp)
{
	this->prg = prg;
	this->intp = intp;

	find_labels();

	for (auto it = prg->lines.begin(); it != prg->lines.end(); ) {
		auto& line = it->second;
		if (line.is_label || line.is_comment) {
			++it;
			continue;
		}
		bool ok = intp->execute_line(line);
		if (!ok || stop_requested)
			break;
		if (branch_requested)
			it = prg->lines.find(branch_target);
		else
			++it;
	}
}

void t_program_runner::stop()
{
	stop_requested = true;
}

void t_program_runner::find_labels()
{
	for (auto& raw_line : prg->lines) {
		auto& line = raw_line.second;
		if (line.is_label) {
			labels[line.label] = line.line_nr;
		}
	}
}
