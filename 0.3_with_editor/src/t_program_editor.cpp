#include "t_program_editor.h"
#include "PTM.h"
#include "t_tile.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "t_util.h"
#include "predefined_charset_ix.h"

t_program_editor::t_program_editor()
{
}

t_program_editor::~t_program_editor()
{
}

void t_program_editor::init(PTM* ptm, t_screen* scr, t_keyboard* kb)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;
	this->snd = &ptm->get_sound();

	first_line_ix = 0;
	last_line_ix = scr->last_row;
}

void t_program_editor::reset()
{
}

void t_program_editor::draw_program()
{
	int scr_y = 0;
	for (int i = first_line_ix; i <= last_line_ix && i < lines.size(); i++) {
		scr->print_string_at(lines[i], 0, scr_y);
		scr_y++;
		if (scr_y > scr->last_row)
			break;
	}
}

void t_program_editor::on_keydown()
{
	SDL_Keycode key = kb->peek_key();

	switch (key)
	{
		case SDLK_RIGHT: {
			kb->ctrl() ?
				scr->move_cursor_next_logical_x(1) :
				scr->move_cursor_dist(1, 0);
			break;
		}
		case SDLK_LEFT: {
			kb->ctrl() ?
				scr->move_cursor_next_logical_x(-1) :
				scr->move_cursor_dist(-1, 0);
			break;
		}
		case SDLK_HOME: {
			scr->move_cursor_line_start();
			break;
		}
		case SDLK_END: {
			scr->move_cursor_eol();
			break;
		}
		case SDLK_BACKSPACE: {
			scr->on_backspace_pressed();
			break;
		}
		case SDLK_DELETE: {
			scr->on_delete_pressed();
			break;
		}
		case SDLK_TAB: {
			for (int i = 0; i < 8; i++)
				scr->on_character_key_pressed(predef_char.whitespace);
			break;
		}
		case SDLK_INSERT: {
			scr->toggle_insert_mode();
			break;
		}
		case SDLK_RETURN: {
			on_enter_pressed();
			break;
		}
		case SDLK_q: {
			if (kb->ctrl())
				ptm->exit();
			break;
		}
		default: {
			unsigned char ch = kb->keycode_to_char(key);
			if (ch > 0) {
				scr->on_character_key_pressed(ch);
				snd->keystroke();
			}
			break;
		}
	}

	kb->pop_key();
}

void t_program_editor::on_enter_pressed()
{
	lines.emplace_back("");
	scr->newline(false);
}
