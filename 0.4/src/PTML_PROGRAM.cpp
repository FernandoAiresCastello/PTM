#include "PTML_PROGRAM.h"
#include "PTML_shared_headers.h"

void PTML::LIST()
{
	ARGC_MIN_MAX(0, 2);

	if (COUNT(0)) {
		for (auto& stored_line : ptm->get_prg().lines) {
			scr->println(stored_line.second.to_string());
		}
	}
	else if (COUNT(1)) {
		t_program& prg = ptm->get_prg();
		int line_nr = NUM(1);
		if (prg.has_line(line_nr)) {
			scr->println(prg.get_line(line_nr)->to_string());
		}
		else {
			error = err.undefined_line_nr;
		}
	}
	else if (COUNT(2)) {
		auto& lines = ptm->get_prg().lines;
		int first = NUM(1);
		int last = NUM(2);
		if (last < first) {
			error = err.arg_out_of_range;
			return;
		}
		auto itLower = lines.lower_bound(first);
		auto itUpper = lines.upper_bound(last);
		for (auto& it = itLower; it != itUpper; ++it) {
			scr->println(it->second.to_string());
		}
	}
}

void PTML::RUN()
{
	REQUIRE_IMM;
	ARGC(0);
	ptm->run_program();
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

void PTML::FN_SET()
{
	REQUIRE_IMM;
	ARGC(2);
	auto&& keyname = STR(1);
	auto&& value = STR(2);
	bool valid = keyname.has_length(2, 3) && (keyname.starts_with("F") || keyname.starts_with("f"));
	if (!valid || !ptm->set_function_key(keyname, value))
		error = err.unknown_fn_keyname;
}
