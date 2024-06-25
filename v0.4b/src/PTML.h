#pragma once
#include "t_string.h"

class PTM;
class t_screen;
class t_program_line;

namespace PTML
{
	extern t_string error;

	void set_env(PTM* _ptm, t_screen* _scr);
	void set_line(t_program_line* _line);

	void COLOR();
}
