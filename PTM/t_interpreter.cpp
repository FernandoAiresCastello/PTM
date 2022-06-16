#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_environment.h"
#include "t_command.h"

t_interpreter::t_interpreter() {
	wnd = nullptr;
	wnd_buf = nullptr;
	running = false;
	user_break = false;
	halted = false;
	branched = false;
	env = nullptr;
	cur_line_ix = 0;
	cmd = nullptr;
	cur_line = nullptr;
}
bool t_interpreter::has_user_break() {
	return user_break;
}
void t_interpreter::run(t_program* prg, TBufferedWindow* wnd) {
	errors.clear();
	env = new t_environment();
	cmd = new t_command(this);
	running = true;
	halted = false;
	branched = false;
	user_break = false;
	cur_line_ix = 0;
	this->wnd = wnd;
	wnd_buf = wnd->GetBuffer();
	wnd_buf->ClearAllLayers();
	wnd->SetBackColor(0);

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

	delete env;
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
void t_interpreter::resolve_vars(t_program_line* line) {
	for (auto& param : line->params) {
		if (param.type == t_param_type::variable) {
			if (env->has_var(param.variable)) {
				param.textual_value = env->get_var(param.variable);
				param.numeric_value = String::ToInt(param.textual_value);
			} else {
				abort("Variable not found");
			}
		}
	}
}
void t_interpreter::execute_current_line() {
	resolve_vars(cur_line);
	string& c = cur_line->cmd;
	auto& args = cur_line->params;

	if (c == "HALT") cmd->halt(args);
	else if (c == "EXIT") cmd->exit(args);
}
