#include "PTML_shared_headers.h"
#include "PTML_ALL.h"
#include "PTML_PROGRAM.h"
#include "PTML_VARS.h"
#include "PTML_CTFLOW.h"
#include "PTML_MATH.h"
#include "PTML_GRAPHICS.h"
#include "PTML_FILESYSTEM.h"
#include "PTML_INPUT.h"
#include "PTML_SPRITES.h"

t_function_ptr PTML::get_cmd_pointer(const t_string& cmd)
{
	// === PROGRAM MANAGEMENT ===
	CMD("LIST", LIST);
	CMD("RUN", RUN);
	CMD("NEW", NEW);
	CMD("RENUM", RENUM);
	CMD("SAVE", SAVE);
	CMD("LOAD", LOAD);
	CMD("CSAVE", CSAVE);
	CMD("CLOAD", CLOAD);
	CMD("PROG", PROG);

	// === SYSTEM CONTROL ===
	CMD("EXIT", EXIT);
	CMD("RESET", RESET);

	// === MEMORY ===
	CMD("SET", SET);
	CMD("VARS", VARS);
	CMD("MEMCLR", MEM_CLR);
	CMD("ALLOC", TBL_NEW);
	CMD("POKE", TBL_SET);
	CMD("PEEK", TBL_GET);

	// === MATH ===
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

	// === CONTROL FLOW ===
	CMD("END", END);
	CMD("HALT", HALT);

	// === GOTO ===
	CMD("GOTO", GOTO);
	CMD("GOTO.E", GOTO_IFE);
	CMD("GOTO.NE", GOTO_IFNE);
	CMD("GOTO.GT", GOTO_IFG);
	CMD("GOTO.GTE", GOTO_IFGE);
	CMD("GOTO.LT", GOTO_IFL);
	CMD("GOTO.LTE", GOTO_IFLE);
	CMD("GOTO.K", GOTO_IFKEY);
	CMD("GOTO.NK", GOTO_IFNKEY);

	// === CALL/RET ===
	CMD("CALL", CALL);
	CMD("CALL.E", CALL_IFE);
	CMD("CALL.NE", CALL_IFNE);
	CMD("CALL.GT", CALL_IFG);
	CMD("CALL.GTE", CALL_IFGE);
	CMD("CALL.LT", CALL_IFL);
	CMD("CALL.LTE", CALL_IFLE);
	CMD("CALL.K", CALL_IFKEY);
	CMD("CALL.NK", CALL_IFNKEY);
	CMD("RET", RET);

	// === TIME ===
	CMD("PAUSE", PAUSE);

	// === FILESYSTEM ===
	CMD("FILES", FILES);
	CMD("FILE.REN", FILE_REN);
	CMD("FILE.DEL", FILE_DEL);
	CMD("DIR.REN", DIR_REN);
	CMD("DIR.DEL", DIR_DEL);
	CMD("MKDIR", MKDIR);
	CMD("CHDIR", CHDIR);
	CMD("QDIR", DIR_Q);


	// === KEYBOARD INPUT ===
	CMD("INKEY", INKEY);
	CMD("KB.FLUSH", KB_FLUSH);
	CMD("FN.SET", FN_SET);
	CMD("FN.LIST", FN_LIST);
	CMD("INPUT", INPUT);

	// === PALETTE & CHARSET ===
	CMD("PAL", PAL);
	CMD("CHR", CHR);
	CMD("QPAL", PAL_Q);
	CMD("QCHR", CHR_Q);
	CMD("PAL.RST", PAL_RESET);
	CMD("CHR.RST", CHR_RESET);
	CMD("PAL.SAVE", PAL_SAVE);
	CMD("CHR.SAVE", CHR_SAVE);
	CMD("PAL.LOAD", PAL_LOAD);
	CMD("CHR.LOAD", CHR_LOAD);

	// === SCREEN ===
	CMD("SCR.ON", SCR_ON);
	CMD("SCR.OFF", SCR_OFF);
	CMD("SCR.FULL", SCR_FULL);
	CMD("REFRESH", REFRESH);
	CMD("CLS", CLS);

	// === COLOR REGISTER ===
	CMD("COLOR", COLOR);
	CMD("QCOLOR", COLOR_Q);
	CMD("COLOR.F", COLOR_SETF);
	CMD("COLOR.B", COLOR_SETB);
	CMD("COLOR.BR", COLOR_SETBR);
	CMD("COLOR.GETF", COLOR_GETF);
	CMD("COLOR.GETB", COLOR_GETB);
	CMD("COLOR.GETBR", COLOR_GETBR);

	// === COLOR MODES ===
	CMD("COLOR.MONO", COLOR_MONO);
	CMD("COLOR.MULTI", COLOR_MULTI);

	// === CURSOR ===
	CMD("CSR.ON", CSR_ON);
	CMD("CSR.OFF", CSR_OFF);
	CMD("LOCATE", LOCATE);

	// === TEXT OUTPUT ===
	CMD("PRINT", PRINT);
	CMD("PRINTL", PRINTL);
	CMD("PRINTF", PRINTF);

	// === TILE REGISTER ===
	CMD("TILE.NEW", TILE_NEW);
	CMD("TILE.ADD", TILE_ADD);
	CMD("QTILE", TILE_Q);
	CMD("TILE.SETP", TILE_SETP);
	CMD("TILE.GETP", TILE_GETP);
	CMD("TILE.SAVE", TILE_SAVE);
	CMD("TILE.LOAD", TILE_LOAD);

	// === TILEBUFFER ===
	CMD("GET", GET);
	CMD("PUT", PUT);
	CMD("RECT", RECT);
	CMD("RECT.DEL", RECT_DEL);
	CMD("LINE.H", LINE_H);
	CMD("LINE.V", LINE_V);
	CMD("FILL", FILL);
	CMD("DEL", DEL);

	// === SPRITES ===
	CMD("SPR.NEW", SPR_NEW);
	CMD("SPR.GRID", SPR_GRID);
	CMD("SPR.POS", SPR_POS);
	CMD("SPR.X", SPR_X);
	CMD("SPR.Y", SPR_Y);
	CMD("SPR.GETX", SPR_GETX);
	CMD("SPR.GETY", SPR_GETY);
	CMD("SPR.SHOW", SPR_SHOW);
	CMD("SPR.MOVE", SPR_MOVE);
	CMD("SPR.DEL", SPR_DEL);
	CMD("SPR.CLR", SPR_CLR);
	CMD("SPR.TGET", SPR_TGET);
	CMD("SPR.TSET", SPR_TSET);

	return nullptr;
}
