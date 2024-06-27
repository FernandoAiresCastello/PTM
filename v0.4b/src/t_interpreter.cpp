#include "t_interpreter.h"
#include "t_lexer.h"
#include "t_program_line.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "PTM.h"
#include "PTML.h"

#define CMD(keyword)	if (cmd == #keyword) return PTML::keyword;

#define ASSIGN_ARG(n) \
	line.arg##n.is_empty = tokens[n].type == t_token_type::empty; \
	line.arg##n.is_identifier = tokens[n].type == t_token_type::identifier; \
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
	CMD(COLOR);
	CMD(VAR);
	CMD(VARS);
	CMD(PRINT);
	CMD(PRINTL);
	CMD(EXIT);
	CMD(HALT);
	CMD(CLS);
	CMD(PAL);
	CMD(CHR);
	CMD(LOCATE);
	CMD(INC);
	CMD(DEC);
	CMD(ADD);
	CMD(SUB);
	CMD(MUL);
	CMD(DIV);
	CMD(MOD);
	CMD(RND);
	CMD(FSCR);

	return nullptr;
}
