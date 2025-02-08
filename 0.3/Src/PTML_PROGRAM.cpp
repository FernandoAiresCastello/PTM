#include "PTML_PROGRAM.h"
#include "PTML_shared_headers.h"

void PTML::LIST()
{
	REQUIRE_IMM;
	ARGC_MIN_MAX(0, 2);
	t_list<t_string> lines;

	if (COUNT(0)) { // List all lines from first to last
		for (auto& stored_line : ptm->get_prg().lines) {
			lines.push_back(stored_line.second.to_string());
		}
	}
	else if (COUNT(1)) {
		auto&& arg = IDENT(1);
		if (isalpha(arg[0])) { // List all lines starting from label
			int line_nr = ptm->find_program_label(arg);
			if (line_nr < 0) {
				error = err.label_not_found;
				return;
			}
			auto& prg_lines = ptm->get_prg().lines;
			auto itLower = prg_lines.lower_bound(line_nr);
			auto itUpper = prg_lines.end();
			for (auto& it = itLower; it != itUpper; ++it) {
				lines.push_back(it->second.to_string());
			}
		}
		else { // List line with number
			t_program& prg = ptm->get_prg();
			int line_nr = NUM(1);
			if (prg.has_line(line_nr)) {
				lines.push_back(prg.get_line(line_nr)->to_string());
			}
			else {
				error = err.undefined_line_nr;
				return;
			}
		}
	}
	else if (COUNT(2)) { // List lines within interval
		auto& prg_lines = ptm->get_prg().lines;
		int first = NUM(1);
		int last = NUM(2);
		if (last < first) {
			error = err.arg_out_of_range;
			return;
		}
		auto itLower = prg_lines.lower_bound(first);
		auto itUpper = prg_lines.upper_bound(last);
		for (auto& it = itLower; it != itUpper; ++it) {
			lines.push_back(it->second.to_string());
		}
	}

	PRINT_LIST(lines);
}

void PTML::RUN()
{
	ARGC_MIN_MAX(0, 1);

	if (IMM) {

		if (COUNT(0)) {
			ptm->run_program_from_immediate_mode();
		}
		else if (COUNT(1)) {
			if (!try_load_program(STR(1)))
				return;
			
			ptm->run_program_from_immediate_mode();
		}
	}
	else {

		if (COUNT(0)) {
			ptm->run_program_from_another_program();
		}
		if (COUNT(1)) {
			if (!try_load_program(STR(1)))
				return;

			ptm->run_program_from_another_program();
		}
	}
}

void PTML::NEW()
{
	REQUIRE_IMM;
	ARGC(0);
	ptm->new_program();
}

void PTML::SAVE()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1).to_upper() + PROGRAM_FILE_EXT;
	VALIDATE_FILENAME(filename);

	if (ptm->get_prg().lines.empty()) {
		error = err.invalid_program;
		return;
	}

	ptm->save_program(filename);
}

void PTML::LOAD()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1).to_upper() + PROGRAM_FILE_EXT;
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	bool valid = try_load_program(filename);
	if (!valid)
		error = err.invalid_program;
}

void PTML::RENUM()
{
	REQUIRE_IMM;
	ARGC_MIN_MAX(0, 1);

	if (COUNT(0)) {
		ptm->renumber_program(10);
	}
	else if (COUNT(1)) {
		int&& interval = NUM(1);
		if (interval <= 0)
			error = err.arg_out_of_range;
		else
			ptm->renumber_program(interval);
	}
}

void PTML::PROG()
{
	REQUIRE_IMM;
	ARGC(0);
	scr->print_string_crlf(ptm->get_last_program_filename());
}
