#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"

t_interpreter::t_interpreter() {
	wnd = nullptr;
	wnd_buf = nullptr;
	running = false;
	user_break = false;
	halted = false;
	cur_line_ix = 0;
}
bool t_interpreter::has_user_break() {
	return user_break;
}
void t_interpreter::run(t_program* prg, TBufferedWindow* wnd) {
	errors.clear();
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
			execute_line(&prg->lines[cur_line_ix]);
			if (branched) {
				branched = false;
			} else {
				cur_line_ix++;
			}
		} else {
			abort(nullptr, "Invalid execution pointer");
		}
	}
}
void t_interpreter::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_RETURN && TKey::Alt()) {
		wnd->ToggleFullscreen();
	} else if (key == SDLK_ESCAPE) {
		user_break = true;
		running = false;
	}
}
void t_interpreter::abort(t_program_line* line, string error) {
	running = false;
	if (line) {
		errors.push_back(String::Format("At line %i:\n%s\n\n%s",
			line->src_line_nr, error.c_str(), line->src.c_str()));
	} else {
		errors.push_back(error);
	}
}
void t_interpreter::resolve_vars(t_program_line* line) {
	for (auto& param : line->params) {
		if (param.type == t_param_type::variable) {
		} else if (param.type == t_param_type::index) {
		}
	}
}
void t_interpreter::argc(t_program_line* line, int expected) {
	if (line->params.size() != expected) {
		abort(line, "Invalid argument count");
	}
}
void t_interpreter::argc(t_program_line* line, int min, int max) {
	if (line->params.size() < min || line->params.size() > max) {
		abort(line, "Invalid argument count");
	}
}
void t_interpreter::execute_line(t_program_line* line) {
	resolve_vars(line);
	string& cmd = line->cmd;
	auto& params = line->params;
	if (cmd == "HALT") {
		argc(line, 0);
		halted = true;
	} else if (cmd == "EXIT") {
		argc(line, 0);
		running = false;
	}
}
