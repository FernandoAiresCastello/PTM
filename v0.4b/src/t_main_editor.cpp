#include "t_main_editor.h"
#include "PTM.h"
#include "t_tile.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "t_util.h"
#include "t_interpreter.h"

void t_main_editor::init(PTM* ptm, t_screen* scr, t_keyboard* kb, t_interpreter* intp)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;
	this->intp = intp;
}

void t_main_editor::print_welcome()
{
	scr->color(default_fg, default_bg, default_bdr);
	scr->show_cursor(true);
	scr->println(ptm->version_string);
	scr->println(intp->prompt);
}

void t_main_editor::on_keydown()
{
	if (!handle_control_key())
		if (!handle_function_key())
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

		case SDLK_DELETE: {
			t_tileflags flags;
			flags.monochrome = true;
			scr->set_blank_tile(scr->csrx(), scr->csry(), flags);
			return true;
		}

		case SDLK_TAB: {
			for (int i = 0; i < 8; i++)
				scr->print(" ");
			return true;
		}

		case SDLK_RETURN: {
			on_enter_pressed();
			return true;
		}
	}

	return false;
}

bool t_main_editor::handle_function_key()
{
	bool shift = kb->shift();

	switch (kb->key)
	{
		case SDLK_F1:
			highlight_line_wrap();
			return true;
		case SDLK_F2:
			return true;
		case SDLK_F3:
			return true;
		case SDLK_F4:
			scr->print("list ");
			if (kb->shift()) on_enter_pressed();
			return true;
		case SDLK_F5:
			scr->print("run");
			on_enter_pressed();
			return true;
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

void t_main_editor::highlight_line_wrap()
{
	for (int y = 0; y <= scr->last_row(); y++) {
		for (int x = 0; x <= scr->last_col(); x++) {
			t_tile& tile = scr->get_tile(t_pos(x, y));
			if (tile.flags.line_wrap) {
				tile.flags.monochrome = false;
				tile.get_char().fgc = 1;
				tile.get_char().bgc = 15;
			}
		}
	}
}

void t_main_editor::on_enter_pressed()
{
	t_string line = scr->get_current_logical_line();
	scr->newline();
	if (!line.trim().empty())
		intp->interpret_line(line);
}
