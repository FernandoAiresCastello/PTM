#pragma once
#include "t_string.h"
#include "t_list.h"
#include "t_token.h"
#include "t_program_line.h"

class PTM;
class t_screen;
class t_keyboard;

class t_interpreter
{
public:
	void init(PTM* ptm, t_screen* scr, t_keyboard* kb);
	void interpret_line(t_string& line, bool from_file = false);
	bool execute_line(t_program_line& line);
	const t_string& get_error();

private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;
};
