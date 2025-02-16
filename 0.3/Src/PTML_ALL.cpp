#include "PTML_shared_headers.h"
#include "PTML_ALL.h"
#include "PTML_PROGRAM.h"
#include "PTML_VARS.h"
#include "PTML_CTFLOW.h"
#include "PTML_MATH.h"
#include "PTML_GRAPHICS.h"
#include "PTML_FILESYSTEM.h"
#include "PTML_INPUT.h"
#include "PTML_SOUND.h"

t_function_ptr PTML::get_cmd_pointer(const t_string& cmd)
{
    // === PROGRAM MANAGEMENT ===
    CMD("LIST", LIST);
    CMD("NEW", NEW);
    CMD("RENUM", RENUM);
    CMD("PROG", PROG);
    CMD("TITLE", TITLE);

    // === SYSTEM CONTROL ===
    CMD("RUN", RUN);
    CMD("END", END);
    CMD("HALT", HALT);
    CMD("EXIT", EXIT);
    CMD("RESET", RESET);
    CMD("PAUSE", PAUSE);
    CMD("BREAK", BREAK);
    CMD("HCF", HCF);

    // === MEMORY ===
    CMD("SET", SET);
    CMD("DIM", ARR_DIM);
    CMD("SWAP", SWAP);
    CMD("MEMCLR", MEMCLR);

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

    // === JUMPS ===
    CMD("GOTO", GOTO);
    CMD("GOTO.E", GOTO_IFE);
    CMD("GOTO.NE", GOTO_IFNE);
    CMD("GOTO.G", GOTO_IFG);
    CMD("GOTO.GE", GOTO_IFGE);
    CMD("GOTO.L", GOTO_IFL);
    CMD("GOTO.LE", GOTO_IFLE);
    CMD("GOTO.K", GOTO_IFKEY);
    CMD("GOTO.NK", GOTO_IFNKEY);

    // === SUBROUTINES ===
    CMD("CALL", CALL);
    CMD("CALL.E", CALL_IFE);
    CMD("CALL.NE", CALL_IFNE);
    CMD("CALL.G", CALL_IFG);
    CMD("CALL.GE", CALL_IFGE);
    CMD("CALL.L", CALL_IFL);
    CMD("CALL.LE", CALL_IFLE);
    CMD("CALL.K", CALL_IFKEY);
    CMD("CALL.NK", CALL_IFNKEY);
    CMD("RET", RET);

    // === FILE SYSTEM ===
    CMD("FILES", FILES);
    CMD("SAVE", SAVE);
    CMD("LOAD", LOAD);
    CMD("RENAME", RENAME);
    CMD("KILL", KILL);
    CMD("OPEN", OPEN);
    CMD("CLOSE", CLOSE);
    CMD("WRITE", WRITE);
    CMD("READ", READ);
    CMD("EOF", FEOF);

    // === KEYBOARD INPUT ===
    CMD("INPUT", INPUT);
    CMD("INKEY", INKEY);
    CMD("FLUSH", KB_FLUSH);

    // === GRAPHICS ===
    CMD("PAL", PAL);
    CMD("CHR", CHR);

    // === SCREEN ===
    CMD("REFRESH", REFRESH);
    CMD("AUTOREF", AUTOREF);
    CMD("FULLSCR", FULLSCR);
    CMD("CLS", CLS);

    // === CURSOR ===
    CMD("CURSOR", CURSOR);
    CMD("LOCATE", LOCATE);
    CMD("XSET", CSR_SETX);
    CMD("YSET", CSR_SETY);
    CMD("XGET", CSR_GETX);
    CMD("YGET", CSR_GETY);

    // === TEXT OUTPUT ===
    CMD("PRINT", PRINT);
    CMD("PRINTL", PRINTL);
    CMD("PRINTF", PRINTF);

    // === COLOR REGISTER ===
    CMD("COLOR", COLOR);
    CMD("INK", COLOR_SETF);
    CMD("PAPER", COLOR_SETB);
    CMD("BORDER", COLOR_SETBR);
    CMD("MODE", COLOR_MODE);

    // === TILE REGISTER ===
    CMD("TILE", TILE_ADD);
    CMD("CSET", TILE_SETC);
    CMD("CGET", TILE_GETC);
    CMD("FSET", TILE_SETF);
    CMD("FGET", TILE_GETF);
    CMD("BSET", TILE_SETB);
    CMD("BGET", TILE_GETB);
    CMD("PSET", TILE_SETP);
    CMD("PGET", TILE_GETP);

    // === TILEBUFFER ===
    CMD("GET", GET);
    CMD("PUT", PUT);
    CMD("DEL", DEL);
    CMD("RECT", RECT);
    CMD("FILL", FILL);

    // === SPRITES ===
    CMD("ENASPR", ENABLE_SPRITES);
    CMD("DELSPR", RESET_SPRITES);
    CMD("SPRITE", SET_SPRITE);
    CMD("MOVETO", MOVE_SPRITE_TO);
    CMD("MOVE", MOVE_SPRITE_DIST);
    CMD("SHOW", SHOW_SPRITE);
    CMD("TILESPR", GET_SPRITE_TILE);
    CMD("SXGET", GET_SPRITE_X);
    CMD("SYGET", GET_SPRITE_Y);
    CMD("CHKCOL", CHECK_SPRITE_COLLISION);

    // === SOUND ===
    CMD("BEEP", BEEP);
    CMD("PLAY", PLAY);

    // === STRINGS ===
    CMD("JOIN", STR_CONCAT);
    CMD("UCASE", STR_UPPER);
    CMD("LCASE", STR_LOWER);
    CMD("FIND", STR_FIND);
    CMD("SUBS", STR_SUBSTR);
    CMD("LEN", STR_LEN);
    CMD("ASC", STR_ASCII);
    CMD("CHAR", STR_CHAR);
    CMD("REPT", STR_REPEAT);

	return nullptr;
}
