#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_game.h"
#include "t_command.h"

t_interpreter::t_interpreter() {
	wnd = nullptr;
	wnd_buf = nullptr;
	running = false;
	user_break = false;
	halted = false;
	branched = false;
	game = nullptr;
	cur_line_ix = 0;
	cmd = nullptr;
	cur_line = nullptr;
	prg = nullptr;
}
bool t_interpreter::has_user_break() {
	return user_break;
}
void t_interpreter::run(t_program* prg, t_game* game, TBufferedWindow* wnd) {
	errors.clear();
	this->prg = prg;
	this->game = game;
	cmd = new t_command(this);
	running = true;
	halted = false;
	branched = false;
	user_break = false;
	cur_line_ix = 0;
	callstack = std::stack<int>();
	this->wnd = wnd;
	wnd_buf = wnd->GetBuffer();
	wnd_buf->ClearAllLayers();
	wnd->SetBackColor(game->bgcolor);

	while (running) {
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		wnd->Update();
		if (e.type == SDL_KEYDOWN) {
			on_keydown(e.key.keysym.sym, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		}
		if (halted) {
			continue;
		}
		if (cur_line_ix >= 0 && cur_line_ix < prg->lines.size()) {
			cur_line = &prg->lines[cur_line_ix];
			execute_current_line();
			if (branched) {
				branched = false;
			} else {
				cur_line_ix++;
			}
		} else {
			cur_line = nullptr;
			abort("Invalid execution pointer");
		}
	}

	delete cmd;
}
void t_interpreter::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_RETURN && TKey::Alt()) {
		wnd->ToggleFullscreen();
	} else if (key == SDLK_ESCAPE) {
		user_break = true;
		running = false;
	}
}
void t_interpreter::abort(string error) {
	running = false;
	if (cur_line) {
		errors.push_back(String::Format("At line %i:\n%s\n\n%s",
			cur_line->src_line_nr, error.c_str(), cur_line->src.c_str()));
	} else {
		errors.push_back(error);
	}
}
bool t_interpreter::argc(t_params& arg, int expected) {
	if (arg.size() != expected) {
		abort("Invalid argument count");
		return false;
	}
	return true;
}
bool t_interpreter::argc(t_params& arg, int min, int max) {
	if (arg.size() < min || arg.size() > max) {
		abort("Invalid argument count");
		return false;
	}
	return true;
}
int t_interpreter::require_number(t_param& arg) {
	if (arg.type == t_param_type::number || 
		arg.type == t_param_type::string || 
		arg.type == t_param_type::char_literal) {
		return arg.numeric_value;
	} else if (arg.type == t_param_type::address_alias) {
		if (game->has_address_alias(arg.address_alias)) {
			return game->get_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_alias) {
		if (game->has_address_alias(arg.address_alias)) {
			return game->peek_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_literal) {
		return game->peek_address(arg.address);
	} else {
		abort("Syntax error");
	}
	return 0;
}
string t_interpreter::require_label(t_param& arg) {
	if (arg.type != t_param_type::label) {
		abort("Label expected");
		return "";
	}
	if (prg->labels.find(arg.label) == prg->labels.end()) {
		abort("Label not found");
		return "";
	}
	return arg.label;
}
int t_interpreter::require_adress_or_alias(t_param& arg) {
	if (arg.type == t_param_type::number) {
		return arg.numeric_value;
	} else if (arg.type == t_param_type::address_alias) {
		if (game->has_address_alias(arg.address_alias)) {
			return game->get_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else {
		abort("Address or alias expected");
	}
	return ILLEGAL_ADDRESS;
}
int t_interpreter::require_aliased_address(t_param& arg) {
	if (arg.type == t_param_type::address_alias) {
		if (game->has_address_alias(arg.address_alias)) {
			return game->get_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else {
		abort("Alias expected");
	}
	return ILLEGAL_ADDRESS;
}
string t_interpreter::require_string(t_param& arg) {
	if (arg.type == t_param_type::string || arg.type == t_param_type::number) {
		return arg.textual_value;
	} else if (arg.type == t_param_type::address_alias) {
		if (game->has_address_alias(arg.address_alias)) {
			return String::ToString(game->get_address_with_alias(arg.address_alias));
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_alias) {
		if (game->has_address_alias(arg.address_alias)) {
			return game->get_string_from_address_with_alias(arg.address_alias);
		} else {
			abort("Undefined alias: " + arg.address_alias);
		}
	} else if (arg.type == t_param_type::address_deref_literal) {
		return game->get_string_from_address(arg.address);
	} else {
		abort("String expected");
	}
	return "";
}
void t_interpreter::execute_current_line() {
	string& c = cur_line->cmd;
	auto& args = cur_line->params;
	cmd->execute(c, args);
}
