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
	ptm->debug(kb->key);

	if (!handle_control_key())
		handle_character_key();
}

bool t_main_editor::handle_control_key()
{
	switch (kb->key)
	{
		case SDLK_RIGHT:	scr->move_cursor_wrap_x(1);		return true;
		case SDLK_LEFT:		scr->move_cursor_wrap_x(-1);	return true;
		case SDLK_DOWN:		scr->move_cursor_dist(0, 1);	return true;
		case SDLK_UP:		scr->move_cursor_dist(0, -1);	return true;

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
			return true;
		}

		case SDLK_END: {
			if (kb->ctrl()) {
				scr->locate(scr->last_col(), scr->last_row());
			}
			else {
				scr->locate(scr->eol(), scr->csry());
			}
			return true;
		}

		case SDLK_BACKSPACE: {
			scr->move_cursor_wrap_x(-1);
			t_tileflags flags;
			flags.monochrome = true;
			scr->set_blank_tile(scr->csrx(), scr->csry(), flags);
			return true;
		}

		case SDLK_RETURN: {
			scr->newline();
			return true;
		}
	}

	return false;
}

bool t_main_editor::handle_character_key()
{
	int ch = kb->keycode_to_char(kb->key);
	if (ch > 0) {
		scr->print(ch);
		return true;
	}
	return false;
}
