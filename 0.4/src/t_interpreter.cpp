#include "t_interpreter.h"
#include "t_tokenizer.h"
#include "t_program_line.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "t_record_file.h"
#include "PTM.h"
#include "PTML_ALL.h"
#include "PTML_runtime.h"
#include "PTML_errors.h"

t_tokenizer tokenizer;
t_list<t_token> tokens;

void t_interpreter::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;

	PTML::set_env(ptm, scr);
}

void t_interpreter::print_prompt()
{
	scr->print_string_crlf(prompt);
}

void t_interpreter::interpret_line(t_string& src, bool from_file)
{
	if (src.contains(t_record_file::delimiter)) {
		PTML::error = PTML::err.bad_file_format;
		return;
	}

	tokenizer.tokenize_line(src, tokens);
	if (tokens.empty())
		return;

	if (tokens[0].type == t_token_type::line_number) {
		int line_number = tokens[0].numeric_val;
		if (tokens.size() == 1 && !from_file) {
			bool ok = ptm->delete_program_line(line_number);
			if (!ok) {
				scr->print_string_crlf(PTML::err.undefined_line_nr);
				print_prompt();
			}
		}
		else {
			tokens.erase(tokens.begin());
			if (tokens.empty()) {
				PTML::error = t_string::fmt(
					PTML::err.invalid_program_line_at.c_str(), line_number);
			}
			else {
				t_program_line line = t_program_line(tokens);
				line.line_nr = line_number;
				line.immediate = false;
				line.src = src;
				ptm->save_program_line(line);
			}
		}
	}
	else {
		t_program_line line = t_program_line(tokens);
		line.immediate = true;
		execute_line(line);
	}
}

bool t_interpreter::execute_line(t_program_line& line)
{
	PTML::set_line(&line);
	PTML::error = "";

	if (line.fn && !line.has_error)
		line.fn();
	else
		PTML::error = PTML::err.syntax_error;

	bool has_error = !PTML::error.empty();

	if (ptm->has_new_program_loaded_at_runtime())
		return has_error;

	if (has_error) {
		scr->move_cursor_line_start();
		if (line.immediate)
			scr->print_string_crlf(PTML::error);
		else
			scr->print_string_crlf(t_string::fmt(
				PTML::err.error_in_linenr.c_str(), PTML::error.c_str(), line.line_nr));

		ptm->get_sound().alert();
	}

	if (line.immediate)
		print_prompt();

	PTML::error = "";
	return !has_error;
}

const t_string& t_interpreter::get_error()
{
	return PTML::error;
}

void t_interpreter::on_user_interrupt(t_program_line* line)
{
	ptm->get_sound().alert();

	scr->newline();
	scr->print_string_crlf(t_string::fmt(
		PTML::err.break_in.c_str(), line->line_nr));
}
