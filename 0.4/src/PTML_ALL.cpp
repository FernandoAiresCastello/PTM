#include "PTML_shared_headers.h"
#include "PTML_ALL.h"
#include "PTML_PROGRAM.h"
#include "PTML_VARS.h"
#include "PTML_CTFLOW.h"
#include "PTML_MATH.h"
#include "PTML_GRAPHICS.h"
#include "PTML_FILESYSTEM.h"
#include "PTML_INPUT.h"

t_function_ptr PTML::get_cmd_pointer(const t_string& cmd)
{
	CMD("VAR", VAR);
	CMD("VARS", VARS);
	CMD("VARS.CLR", VAR_CLR);
	CMD("COLOR", COLOR);
	CMD("COLOR.MONO", COLOR_MONO);
	CMD("COLOR.MULTI", COLOR_MULTI);
	CMD("COLOR.SETF", COLOR_SETF);
	CMD("COLOR.SETB", COLOR_SETB);
	CMD("COLOR.SETBR", COLOR_SETBR);
	CMD("COLOR.GETF", COLOR_GETF);
	CMD("COLOR.GETB", COLOR_GETB);
	CMD("COLOR.GETBR", COLOR_GETBR);
	CMD("PRINT", PRINT);
	CMD("PRINTC", PRINTC);
	CMD("PRINTL", PRINTL);
	CMD("PRINTF", PRINTF);
	CMD("EXIT", EXIT);
	CMD("HALT", HALT);
	CMD("RESET", RESET);
	CMD("CLS", CLS);
	CMD("PAL", PAL);
	CMD("CHR", CHR);
	CMD("PAL.OUT", PAL_OUT);
	CMD("CHR.OUT", CHR_OUT);
	CMD("PAL.RESET", PAL_RESET);
	CMD("CHR.RESET", CHR_RESET);
	CMD("LOCATE", LOCATE);
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
	CMD("SCR.FULL", SCR_FULL);
	CMD("SCR.ON", SCR_ON);
	CMD("SCR.OFF", SCR_OFF);
	CMD("REFRESH", REFRESH);
	CMD("CSR.ON", CSR_ON);
	CMD("CSR.OFF", CSR_OFF);
	CMD("TILE.NEW", TILE_NEW);
	CMD("TILE.ADD", TILE_ADD);
	CMD("TILE.LIST", TILE_LIST);
	CMD("TILE.LISTC", TILE_LISTC);
	CMD("GET", GET);
	CMD("PUT", PUT);
	CMD("RECT", RECT);
	CMD("RECT.DEL", RECT_DEL);
	CMD("FILL", FILL);
	CMD("DEL", DEL);
	CMD("LIST", LIST);
	CMD("RUN", RUN);
	CMD("END", END);
	CMD("NEW", NEW);
	CMD("RENUM", RENUM);
	CMD("SAVE", SAVE);
	CMD("SAVE.SRC", SAVE_SRC);
	CMD("LOAD", LOAD);
	CMD("LOAD.SRC", LOAD_SRC);
	CMD("FILES", FILES);
	CMD("FILE.NAME", FILE_NAME);
	CMD("GOTO", GOTO);
	CMD("GOTO.E", GOTO_IFE);
	CMD("GOTO.NE", GOTO_IFNE);
	CMD("GOTO.GT", GOTO_IFG);
	CMD("GOTO.GTE", GOTO_IFGE);
	CMD("GOTO.LT", GOTO_IFL);
	CMD("GOTO.LTE", GOTO_IFLE);
	CMD("GOTO.K", GOTO_IFKEY);
	CMD("GOTO.NK", GOTO_IFNKEY);
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
	CMD("INKEY", INKEY);
	CMD("KB.FLUSH", KB_FLUSH);
	CMD("FN.SET", FN_SET);
	CMD("FN.LIST", FN_LIST);
	CMD("INPUT", INPUT);

	return nullptr;
}
