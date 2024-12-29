#include <SDL.h>
#include "t_main_editor.h"
#include "PTM.h"
#include "t_tile.h"
#include "t_screen.h"
#include "t_keyboard.h"
#include "t_util.h"
#include "t_interpreter.h"
#include "predefined_charset_ix.h"

void t_main_editor::init(PTM* ptm, t_screen* scr, t_keyboard* kb, t_interpreter* intp)
{
	this->ptm = ptm;
	this->scr = scr;
	this->kb = kb;
	this->intp = intp;
	this->snd = &ptm->get_sound();

	reset();
}

void t_main_editor::reset()
{
	function_keys[SDLK_F1] = "";
	function_keys[SDLK_F2] = "color ";
	function_keys[SDLK_F3] = "files ";
	function_keys[SDLK_F4] = "list ";
	function_keys[SDLK_F5] = "run\n";
	function_keys[SDLK_F6] = "save ";
	function_keys[SDLK_F7] = "load ";
	function_keys[SDLK_F8] = "";
	function_keys[SDLK_F9] = "";
	function_keys[SDLK_F10] = "";

	function_keys_shifted[SDLK_F1] = "";
	function_keys_shifted[SDLK_F2] = t_string::fmt("color %i,%i,%i\n", scr->default_fg, scr->default_bg, scr->default_bdr);
	function_keys_shifted[SDLK_F3] = "files\n";
	function_keys_shifted[SDLK_F4] = "list\n";
	function_keys_shifted[SDLK_F5] = "";
	function_keys_shifted[SDLK_F6] = "";
	function_keys_shifted[SDLK_F7] = "";
	function_keys_shifted[SDLK_F8] = "";
	function_keys_shifted[SDLK_F9] = "";
	function_keys_shifted[SDLK_F10] = "";
}

void t_main_editor::print_welcome(bool show_prompt)
{
	if (!active)
		return;

	scr->print_string_crlf(ptm->version_string);
	scr->print_string_crlf(ptm->title_short);
	scr->print_string_crlf(ptm->copyright_notice);

	if (show_prompt)
		intp->print_prompt();
}

void t_main_editor::on_keydown()
{
	if (!handle_control_key()) {
		if (!handle_function_key()) {
			handle_character_key();
		}
	}
	kb->pop_key();
}

bool t_main_editor::handle_control_key()
{
	switch (kb->peek_key())
	{
		case SDLK_RIGHT:
			kb->ctrl() ? 
				scr->move_cursor_next_logical_x(1) :
				scr->move_cursor_dist(1, 0);
			return true;

		case SDLK_LEFT:
			kb->ctrl() ? 
				scr->move_cursor_next_logical_x(-1) :
				scr->move_cursor_dist(-1, 0);	
			return true;

		case SDLK_DOWN:		scr->move_cursor_dist(0, 1);	return true;
		case SDLK_UP:		scr->move_cursor_dist(0, -1);	return true;

		case SDLK_HOME: {
			if (kb->shift()) {
				scr->move_cursor_top_left();
				scr->clear();
				scr->set_insert_mode(false);
			}
			else if (kb->ctrl()) {
				scr->move_cursor_top_left();
			}
			else {
				scr->move_cursor_line_start();
			}
			return true;
		}

		case SDLK_END: {
			scr->move_cursor_eol();
			return true;
		}

		case SDLK_BACKSPACE: {
			scr->on_backspace_pressed();
			return true;
		}

		case SDLK_DELETE: {
			scr->on_delete_pressed();
			return true;
		}

		case SDLK_TAB: {
			for (int i = 0; i < 8; i++)
				scr->on_character_key_pressed(predef_char.whitespace);
			return true;
		}

		case SDLK_INSERT: {
			scr->toggle_insert_mode();
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

	switch (key)
	{
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
	unsigned char ch = kb->keycode_to_char(kb->peek_key());

	if (ch > 0) {
		if (kb->ctrl())
			return handle_ctrl_character_key();

		scr->on_character_key_pressed(ch);
		snd->keystroke();

		return true;
	}

	return false;
}

bool t_main_editor::handle_ctrl_character_key()
{
	switch (kb->peek_key())
	{
		case SDLK_c: {
			return true;
		}
		case SDLK_x: {
			return true;
		}
		case SDLK_v: {
			return true;
		}
	}

	return false;
}

void t_main_editor::on_enter_pressed()
{
	if (!scr->is_cursor_on_logical_line())
		return;

	t_string&& line = scr->get_current_logical_line();
	scr->newline();
	if (!line.trim().empty())
		intp->interpret_line(line);
}

void t_main_editor::trigger_function_key(SDL_Keycode key, bool shift)
{
	const t_string& text = shift ? function_keys_shifted[key] : function_keys[key];

	if (text.ends_with("\n") || text.ends_with("\\n")) {

		if (text.ends_with("\n")) 
			auto_type(text.remove_last(1));
		if (text.ends_with("\\n")) 
			auto_type(text.remove_last(2));

		on_enter_pressed();
	}
	else {
		auto_type(text);
	}
}

void t_main_editor::auto_type(const t_string& str)
{
	for (auto& ch : str.s_str()) {
		scr->on_character_key_pressed(ch);
	}
}
