#pragma once
#include "t_string.h"
#include "t_list.h"
#include "t_token.h"
#include "t_program_line.h"
#include "t_function_ptr.h"

class PTM;
class t_screen;
class t_keyboard;

class t_interpreter
{
public:
	void init(PTM* ptm, t_screen* scr, t_keyboard* kb);
	void interpret_line(const t_string& line);

private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;

	void execute_line(t_program_line& line);
	t_program_line make_program_line(const t_list<t_token>& tokens);
	t_function_ptr get_fn_by_cmd(const t_string& cmd);
};
