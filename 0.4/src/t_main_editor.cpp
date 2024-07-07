#include <SDL.h>
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

	reset();
}

void t_main_editor::reset()
{
	function_keys[SDLK_F1] = "";
	function_keys[SDLK_F2] = "color ";
	function_keys[SDLK_F3] = "vars\n";
	function_keys[SDLK_F4] = "list ";
	function_keys[SDLK_F5] = "run\n";
	function_keys[SDLK_F6] = "files\n";
	function_keys[SDLK_F7] = "save ";
	function_keys[SDLK_F8] = "load ";
	function_keys[SDLK_F9] = "fn.set ";
	function_keys[SDLK_F10] = "";

	function_keys_shifted[SDLK_F1] = "";
	function_keys_shifted[SDLK_F2] = t_string::fmt("color %i,%i,%i\n", scr->default_fg, scr->default_bg, scr->default_bdr);
	function_keys_shifted[SDLK_F3] = "";
	function_keys_shifted[SDLK_F4] = "list\n";
	function_keys_shifted[SDLK_F5] = "";
	function_keys_shifted[SDLK_F6] = "";
	function_keys_shifted[SDLK_F7] = "";
	function_keys_shifted[SDLK_F8] = "";
	function_keys_shifted[SDLK_F9] = "";
	function_keys_shifted[SDLK_F10] = "";
}

void t_main_editor::print_welcome()
{
	scr->println(ptm->version_string);
	scr->println(intp->prompt);
}

void t_main_editor::on_keydown()
{
	if (!handle_control_key())
		if (!handle_function_key())
			handle_character_key();

	kb->pop_key();
}

bool t_main_editor::handle_control_key()
{
	switch (kb->peek_key())
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
			scr->set_blank_tile(scr->csrx(), scr->csry(), t_tileflags());
			return true;
		}

		case SDLK_DELETE: {
			scr->set_blank_tile(scr->csrx(), scr->csry(), t_tileflags());
			return true;
		}

		case SDLK_TAB: {
			for (int i = 0; i < 8; i++)
				scr->print(" ");
			return true;
		}

		case SDLK_RETURN:
		case SDLK_KP_ENTER: {
			on_enter_pressed();
			return true;
		}
	}

	return false;
}

bool t_main_editor::handle_function_key()
{
	SDL_Keycode&& key = kb->peek_key();

	switch (key) {
		case SDLK_F1:
		case SDLK_F2:
		case SDLK_F3:
		case SDLK_F4:
		case SDLK_F5:
		case SDLK_F6:
		case SDLK_F7:
		case SDLK_F8:
		case SDLK_F9:
		case SDLK_F10:
			trigger_function_key(key, kb->shift());
			return true;
	}

	return false;
}

bool t_main_editor::handle_character_key()
{
	int ch = kb->keycode_to_char(kb->peek_key());
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

void t_main_editor::trigger_function_key(SDL_Keycode key, bool shift)
{
	const t_string& text = shift ? function_keys_shifted[key] : function_keys[key];
	if (text.ends_with("\n") || text.ends_with("\\n")) {
		if (text.ends_with("\n")) scr->print(text.remove_last(1));
		if (text.ends_with("\\n")) scr->print(text.remove_last(2));
		on_enter_pressed();
	}
	else {
		scr->print(text);
	}
}
