#pragma once
#include "t_string.h"

class PTM;
class t_screen;
class t_keyboard;

class t_interpreter
{
public:
	void init(PTM* ptm, t_screen* scr, t_keyboard* kb);
	void exec_immediate(const t_string& line);
	
private:
	PTM* ptm = nullptr;
	t_screen* scr = nullptr;
	t_keyboard* kb = nullptr;
};
