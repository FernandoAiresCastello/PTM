#include "t_interpreter.h"

void t_interpreter::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;
}

void t_interpreter::exec_immediate(const t_string& line)
{
}
