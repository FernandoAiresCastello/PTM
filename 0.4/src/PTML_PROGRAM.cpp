#include "PTML_PROGRAM.h"
#include "PTML_shared_headers.h"

void PTML::LIST()
{
	REQUIRE_IMM;
	ARGC_MIN_MAX(0, 2);
	t_list<t_string> lines;

	if (COUNT(0)) {
		for (auto& stored_line : ptm->get_prg().lines) {
			lines.push_back(stored_line.second.to_string());
		}
	}
	else if (COUNT(1)) {
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
	else if (COUNT(2)) {
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

	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	ptm->save_program(filename, true);
}

void PTML::LOAD()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	if (t_filesystem::file_exists(filename)) {
		bool valid = ptm->load_program(filename, true);
		if (!valid) {
			error = err.invalid_program;
		}
	}
	else {
		error = err.file_not_found;
	}
}

void PTML::SAVE_SRC()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	ptm->save_program(filename, false);
}

void PTML::LOAD_SRC()
{
	REQUIRE_IMM;
	ARGC(1);

	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	if (t_filesystem::file_exists(filename)) {
		bool valid = ptm->load_program(filename, false);
		if (!valid) {
			error = err.invalid_program;
		}
	}
	else {
		error = err.file_not_found;
	}
}

void PTML::PROG()
{
	REQUIRE_IMM;
	ARGC(0);

	if (!ptm->get_last_program_filename().empty())
		scr->print_string_crlf(ptm->get_last_program_filename());
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
