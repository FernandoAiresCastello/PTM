#include "PTML.h"
#include "PTM.h"
#include "t_screen.h"
#include "t_program_line.h"

PTM* ptm = nullptr;
t_screen* scr = nullptr;
t_program_line* line = nullptr;

t_string PTML::error;

void PTML::set_env(PTM* _ptm, t_screen* _scr)
{
	ptm = _ptm;
	scr = _scr;
}

void PTML::set_line(t_program_line* _line)
{
	line = _line;
}

void PTML::COLOR()
{
	if (line->argc == 3) {
		scr->color(line->arg1.numeric_val, line->arg2.numeric_val, line->arg3.numeric_val);
	}
	else if (line->argc == 2) {
		scr->color_fg(line->arg1.numeric_val);
		scr->color_bg(line->arg2.numeric_val);
	}
	else if (line->argc == 1) {
		scr->color_fg(line->arg1.numeric_val);
	}
	else {
		error = "Invalid argument count";
	}
}
