#include "t_interpreter.h"
#include "PTM.h"
#include "PTML.h"
#include "t_tokenizer.h"
#include "t_program_line.h"
#include "t_screen.h"
#include "t_keyboard.h"

#define CMD(k, fn)		if (cmd == k) return PTML::fn

t_tokenizer tokenizer;
t_list<t_token> tokens;

void t_interpreter::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;

	PTML::set_env(ptm, scr);
}

void t_interpreter::interpret_line(t_string& src, bool from_file)
{
	tokenizer.tokenize_line(src, tokens);
	if (tokens.empty())
		return;

	if (tokens[0].type == t_token_type::line_number) {
		int line_number = tokens[0].numeric_val;
		if (tokens.size() == 1 && !from_file) {
			bool ok = ptm->delete_program_line(line_number);
			if (!ok) {
				scr->println("Undefined line number");
				scr->println(prompt);
			}
		}
		else {
			tokens.erase(tokens.begin());
			if (tokens.empty()) {
				PTML::error = t_string::fmt("Invalid program line at %i", line_number);
			}
			else {
				t_program_line line = make_program_line(tokens);
				line.line_nr = line_number;
				line.immediate = false;
				line.src = src;
				ptm->save_program_line(line);
			}
		}
	}
	else {
		t_program_line line = make_program_line(tokens);
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
		PTML::error = "Syntax error";

	bool has_error = !PTML::error.empty();

	if (has_error) {
		if (line.immediate)
			scr->println(PTML::error);
		else
			scr->println(t_string::fmt("%s in %i", PTML::error.c_str(), line.line_nr));
	}

	if (line.immediate)
		scr->println(prompt);

	PTML::error = "";
	return !has_error;
}

const t_string& t_interpreter::get_last_error()
{
	return PTML::error;
}

void t_interpreter::on_user_interrupt(t_program_line* line)
{
	scr->println(t_string::fmt("Break in %i", line->line_nr));
}

t_program_line t_interpreter::make_program_line(const t_list<t_token>& tokens)
{
	t_program_line line;
	const t_token_type& type = tokens[0].type;

	if (type == t_token_type::command_or_identifier) {
		const t_string& cmd = tokens[0].string_val.to_upper();
		line.fn = get_fn_by_cmd(cmd);
		line.argc = int(tokens.size() - 1);

		if (line.argc > 0) line.arg1 = t_param(tokens[1]);
		if (line.argc > 1) line.arg2 = t_param(tokens[2]);
		if (line.argc > 2) line.arg3 = t_param(tokens[3]);
		if (line.argc > 3) line.arg4 = t_param(tokens[4]);
		if (line.argc > 4) line.arg5 = t_param(tokens[5]);
	}
	else if (type == t_token_type::label) {
		line.is_label = true;
		line.label = tokens[0].string_val;
	}
	else if (type == t_token_type::comment) {
		line.is_comment = true;
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
	CMD("COLOR.F", COLOR_F);
	CMD("COLOR.B", COLOR_B);
	CMD("COLOR.BD", COLOR_BD);
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
	CMD("CSR.SET", CSR_SET);
	CMD("TILE.NEW", TILE_NEW);
	CMD("TILE.ADD", TILE_ADD);
	CMD("TILE.LIST", TILE_LIST);
	CMD("GET", GET);
	CMD("PUT", PUT);
	CMD("LIST", LIST);
	CMD("RUN", RUN);
	CMD("END", END);
	CMD("NEW", NEW);
	CMD("SAVE", SAVE);
	CMD("LOAD", LOAD);
	CMD("FILES", FILES);
	CMD("GOTO", GOTO);
	CMD("GOTO.E", GOTO_IFE);

	return nullptr;
}
