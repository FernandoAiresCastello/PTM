#include "t_interpreter.h"
#include "t_lexer.h"
#include "t_program_line.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "PTM.h"
#include "PTML.h"

#define CMD(k, fn)		if (cmd == k) return PTML::fn;

#define ASSIGN_ARG(n) \
	line.arg##n.type = tokens[n].type; \
	line.arg##n.string_val = tokens[n].string_value; \
	line.arg##n.numeric_val = tokens[n].numeric_value;

t_lexer lexer;

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
		t_program_line line = make_program_line(tokens);
		execute_line(line);
	}
}

void t_interpreter::execute_line(t_program_line& line)
{
	PTML::set_line(&line);
	PTML::error = "";

	if (line.fn && !line.has_error)
		line.fn();
	else
		PTML::error = "Syntax error";

	if (!PTML::error.empty())
		scr->println(PTML::error);

	scr->println("Ok");
}

t_program_line t_interpreter::make_program_line(const t_list<t_token>& tokens)
{
	t_program_line line;

	const t_token_type& type = tokens[0].type;

	if (type == t_token_type::command) {
		const t_string& cmd = tokens[0].string_value;
		line.fn = get_fn_by_cmd(cmd);
		line.argc = int(tokens.size() - 1);

		if (line.argc > 0) { ASSIGN_ARG(1); }
		if (line.argc > 1) { ASSIGN_ARG(2); }
		if (line.argc > 2) { ASSIGN_ARG(3); }
		if (line.argc > 3) { ASSIGN_ARG(4); }
		if (line.argc > 4) { ASSIGN_ARG(5); }
	}
	else if (type == t_token_type::label) {
	}

	for (auto& token : tokens) {
		if (token.type == t_token_type::invalid) {
			line.has_error = true;
			break;
		}
	}

	return line;
}

t_function_ptr t_interpreter::get_fn_by_cmd(const t_string& cmd)
{
	CMD("VAR", VAR);
	CMD("VARS", VARS);
	CMD("COLOR", COLOR);
	CMD("PRINT", PRINT);
	CMD("PRINTL", PRINTL);
	CMD("EXIT", EXIT);
	CMD("HALT", HALT);
	CMD("CLS", CLS);
	CMD("PAL", PAL);
	CMD("CHR", CHR);
	CMD("LOCATE", LOCATE);
	CMD("INC", INC);
	CMD("DEC", DEC);
	CMD("ADD", ADD);
	CMD("SUB", SUB);
	CMD("MUL", MUL);
	CMD("DIV", DIV);
	CMD("DIVR", DIVR);
	CMD("POW", POW);
	CMD("SQRT", SQRT);
	CMD("RND", RND);
	CMD("SWAP", SWAP);
	CMD("FSCR", FSCR);
	CMD("CSR.ON", CSR_ON);
	CMD("TILE.NEW", TILE_NEW);
	CMD("TILE.ADD", TILE_ADD);
	CMD("TILE.LIST", TILE_LIST);
	CMD("GET", GET);
	CMD("PUT", PUT);

	return nullptr;
}
