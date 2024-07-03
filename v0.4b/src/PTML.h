#pragma once
#include "t_string.h"
#include "t_param.h"

class PTM;
class t_screen;
class t_program_line;

namespace PTML
{
	extern t_string error;

	enum class t_comparison { eq, neq, gt, gte, lt, lte };
	enum class t_branch_mode { go_to, call };

	void set_env(PTM* _ptm, t_screen* _scr);
	void set_line(t_program_line* _line);
	t_string resolve_str(const t_param& arg);
	int resolve_num(const t_param& arg);
	void branch_unconditional(t_branch_mode mode);
	void branch_conditional(t_comparison cp, t_branch_mode mode);

	void COLOR();
	void COLOR_F();
	void COLOR_B();
	void COLOR_BD();
	void VARS();
	void PRINT();
	void PRINTL();
	void VAR();
	void EXIT();
	void HALT();
	void CLS();
	void PAL();
	void CHR();
	void LOCATE();
	void INC();
	void DEC();
	void ADD();
	void SUB();
	void MUL();
	void DIV();
	void DIVR();
	void POW();
	void SQRT();
	void RND();
	void SWAP();
	void FSCR();
	void CSR_SET();
	void TILE_NEW();
	void TILE_ADD();
	void TILE_LIST();
	void PUT();
	void GET();
	void LIST();
	void RUN();
	void END();
	void NEW();
	void SAVE();
	void LOAD();
	void FILES();
	void GOTO();
	void GOTO_IFE();
	void GOTO_IFNE();
	void GOTO_IFG();
	void GOTO_IFGE();
	void GOTO_IFL();
	void GOTO_IFLE();
	void CALL();
	void RET();
}
