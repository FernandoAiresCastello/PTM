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
	void interpret_line(const t_string& line);

private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;

	void execute_line(t_program_line& line);
};
