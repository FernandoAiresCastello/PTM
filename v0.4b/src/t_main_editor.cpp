#include "t_main_editor.h"
#include "PTM.h"
#include "t_tile.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "t_util.h"

void t_main_editor::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;
}

void t_main_editor::print_welcome()
{
	scr->color(0xa8, 0xa3, 0xa2);
	scr->println("PTM 0.4");
	scr->println("Ok");
	scr->show_cursor(true);
}

void t_main_editor::on_keydown()
{
	switch (kb->key)
	{
		case SDLK_RIGHT:	scr->move_cursor(1, 0); break;
		case SDLK_LEFT:		scr->move_cursor(-1, 0); break;
		case SDLK_DOWN:		scr->move_cursor(0, 1); break;
		case SDLK_UP:		scr->move_cursor(0, -1); break;

		case SDLK_HOME: {
			if (kb->shift()) {
				scr->locate(0, 0);
				scr->clear();
			}
			else if (kb->ctrl()) {
				scr->locate(0, 0);
			}
			else {
				scr->locate(0, scr->csry());
			}
			break;
		}

		case SDLK_END: {
			if (kb->ctrl()) {
				scr->locate(scr->last_col(), scr->last_row());
			}
			else {
				scr->locate(scr->eol(), scr->csry());
			}
			break;
		}
	}
}
