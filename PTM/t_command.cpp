#include "t_command.h"
#include "t_interpreter.h"
#include "t_game.h"
#include "t_program.h"

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	game = intp->game;
}
void t_command::halt(t_params& arg) {
	intp->argc(arg, 0);
	intp->halted = true;
}
void t_command::exit(t_params& arg) {
	intp->argc(arg, 0);
	intp->running = false;
}
void t_command::set_wnd_bgcolor(t_params& arg) {
	intp->argc(arg, 1);
	game->bgcolor = intp->require_number(arg[0]);
}
void t_command::set_text_fgcolor(t_params& arg) {
	intp->argc(arg, 1);
	game->text.fg = intp->require_number(arg[0]);
}
void t_command::set_text_bgcolor(t_params& arg) {
	intp->argc(arg, 1);
	game->text.bg = intp->require_number(arg[0]);
}
void t_command::set_text_colors(t_params& arg) {
	intp->argc(arg, 1, 2);
	if (arg.size() == 1) {
		game->text.fg = intp->require_number(arg[0]);
		game->text.bg = game->bgcolor;
	} else if (arg.size() == 2) {
		game->text.fg = intp->require_number(arg[0]);
		game->text.bg = intp->require_number(arg[1]);
	}
}
void t_command::clear_screen(t_params& arg) {
	intp->argc(arg, 0);
	intp->wnd->SetBackColor(game->bgcolor);
	intp->wnd_buf->ClearAllLayers();
}
void t_command::update_screen(t_params& arg) {
	intp->argc(arg, 0);
	intp->wnd->Update();
}
void t_command::print_text(t_params& arg) {
	intp->argc(arg, 1);
	string str = intp->require_string(arg[0]);
	for (auto& ch : str) {
		intp->wnd_buf->SetTile(TTile(ch, game->text.fg, game->text.bg),
			game->text.layer, game->text.x, game->text.y, false);
		game->text.x++;
	}
}
void t_command::print_char(t_params& arg) {
	intp->argc(arg, 1);
	int ch = intp->require_number(arg[0]);
	if (ch < 0 || ch >= intp->wnd->GetCharset()->GetSize()) {
		intp->abort(String::Format("Invalid charset index: %i", ch));
		return;
	}
	intp->wnd_buf->SetTile(TTile(ch, game->text.fg, game->text.bg),
		game->text.layer, game->text.x, game->text.y, false);
	game->text.x++;
}
void t_command::set_text_cursor_pos(t_params& arg) {
	intp->argc(arg, 2);
	game->text.x = intp->require_number(arg[0]);
	game->text.y = intp->require_number(arg[1]);
}
void t_command::add_tile(t_params& arg) {
	intp->argc(arg, 6);
	int layer = intp->require_number(arg[0]);
	int x = intp->require_number(arg[1]);
	int y = intp->require_number(arg[2]);
	int ch = intp->require_number(arg[3]);
	int fg = intp->require_number(arg[4]);
	int bg = intp->require_number(arg[5]);
	intp->wnd_buf->GetTile(layer, x, y).Add(TTile(ch, fg, bg));
}
void t_command::delete_tile(t_params& arg) {
	intp->argc(arg, 6);
	int layer = intp->require_number(arg[0]);
	int x = intp->require_number(arg[1]);
	int y = intp->require_number(arg[2]);
	intp->wnd_buf->EraseTile(layer, x, y);
}
void t_command::branch(t_params& arg) {
	intp->argc(arg, 1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->cur_line_ix = intp->prg->labels[label];
		intp->branched = true;
	}
}
void t_command::define_alias(t_params& arg) {
	if (!intp->argc(arg, 2)) return;

	if (arg[0].type != t_param_type::address_alias) {
		intp->abort("Alias expected");
		return;
	}
	if (arg[1].type == t_param_type::address_alias) {
		if (game->has_address_alias(arg[1].address_alias)) {
			game->address_alias[arg[0].address_alias] = game->get_address_with_alias(arg[1].address_alias);
		} else {
			intp->abort("Undefined alias: " + arg[1].address_alias);
		}
	} else {
		game->address_alias[arg[0].address_alias] = arg[1].numeric_value;
	}
}
void t_command::poke(t_params& arg) {
	intp->argc(arg, 2);
	if (arg[1].type == t_param_type::string) {
		poke_string(arg);
	} else {
		int address = intp->require_adress_or_alias(arg[0]);
		int value = intp->require_number(arg[1]);
		game->poke_address(address, value);
	}
}
void t_command::poke_string(t_params& arg) {
	intp->argc(arg, 2);
	int address = intp->require_adress_or_alias(arg[0]);
	string value = intp->require_string(arg[1]);
	for (char& ch : value) {
		game->poke_address(address, ch);
		address++;
		if (address >= MEMORY_TOP) {
			break;
		}
	}
	game->poke_address(address, 0);
}
