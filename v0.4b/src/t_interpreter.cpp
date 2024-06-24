#include "t_interpreter.h"
#include "PTM.h"
#include "t_lexer.h"
#include "t_parser.h"

t_lexer lexer;
t_parser parser;
t_list<t_token> tokens;

void t_interpreter::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;
}

void t_interpreter::interpret(const t_string& line)
{
	lexer.tokenize_line(line, tokens);
	if (tokens.empty())
		return;

	if (tokens[0].type == t_token_type::line_number)
		ptm->save_program_line(tokens);
	else
		execute(tokens);
}

void t_interpreter::execute(const t_list<t_token>& tokens)
{
	parser.parse(tokens);

	if (!parser.errors.empty()) {

	}
}
