#pragma once
#include "PTM.h"
#include "t_string.h"
#include "t_screen.h"
#include "t_param.h"
#include "t_program_line.h"
#include "t_pointers.h"
#include "t_tilebuffer.h"
#include "t_sprite.h"

namespace PTML
{
	extern PTM* ptm;
	extern t_screen* scr;
	extern t_program_line* line;
	extern t_string error;

	enum class t_comparison { eq, neq, gt, gte, lt, lte };
	enum class t_branch_mode { go_to, call };

	void set_env(PTM* _ptm, t_screen* _scr);
	void set_line(t_program_line* _line);
	t_string resolve_str(const t_param& arg);
	int resolve_num(const t_param& arg);
	void branch_to(const t_string& label, t_branch_mode mode);
	void branch_unconditional(t_branch_mode mode);
	void branch_conditional(t_comparison cp, t_branch_mode mode);
	void branch_if_keypress(t_branch_mode mode, bool positive);
	bool try_load_program(const t_string& filename);
}
