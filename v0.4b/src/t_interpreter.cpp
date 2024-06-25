#include <cassert>
#include "t_interpreter.h"
#include "PTM.h"
#include "PTML.h"
#include "t_lexer.h"
#include "t_parser.h"
#include "t_program_line.h"
#include "t_screen.h"
#include "t_keyboard.h"

t_lexer lexer;
t_parser parser;

void t_interpreter::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;

	PTML::set_env(ptm, scr);
}

void t_interpreter::interpret_line(const t_string& line)
{
	t_list<t_token> tokens;
	lexer.tokenize_line(line, tokens);
	if (tokens.empty())
		return;

	if (tokens[0].type == t_token_type::line_number) {
		ptm->save_program_line(tokens);
	}
	else {
		t_program_line line = parser.parse_line(tokens);
		if (parser.errors.empty()) {
			execute_line(line);
		}
		else {
			__debugbreak();
		}
	}
}

void t_interpreter::execute_line(t_program_line& line)
{
	PTML::set_line(&line);
	PTML::error = "";

	if (line.fn)
		line.fn();
	else
		PTML::error = "Unknown command";

	if (!PTML::error.empty())
		scr->println(PTML::error);

	scr->println("Ok");
}
