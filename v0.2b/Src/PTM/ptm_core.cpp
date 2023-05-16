#include "ptm_core.h"
#include "ptm_commands.h"
#include "ptm_graphics.h"
#include "../PTML/t_program.h"
#include "../PTML/t_compiler.h"
#include "../PTML/t_interpreter.h"

t_interpreter* intp = nullptr;

void ptm_run(string program_file)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	ptm_init_commands();

	t_program* prg = new t_program();
	if (!prg->load_plain(program_file)) {
		delete prg;     prg = nullptr;
		return;
	}
	t_compiler* compiler = new t_compiler();
	compiler->run(prg);
	if (!compiler->errors.empty()) {
		ptm_abort(compiler->errors[0]);
	}
	if (compiler->has_window_def) {
		auto& wnd = compiler->window_def;
		ptm_init_window(wnd.width, wnd.height, wnd.size, wnd.bgcol);
	}
	else {
		ptm_init_window(360, 200, 3, 0x101010);
	}
	delete compiler;    compiler = nullptr;

	intp = new t_interpreter();
	intp->on_exec_line = ptm_on_exec_line;
	intp->on_keydown = ptm_on_keydown;
	intp->on_idle_loop = ptm_idle_frame;
	intp->run(prg);

	delete intp;    intp = nullptr;
	delete prg;     prg = nullptr;
}
void ptm_exit()
{
	ptm_free_window();
	SDL_Quit();
	exit(0);
}
void ptm_halt()
{
	while (true) {
		ptm_update();
	}
}
void ptm_abort(string msg)
{
	if (intp) {
		intp->abort(msg.c_str());
		MsgBox::Error(PTM_MSGBOX_TITLE, intp->errors[0]);
	}
	else {
		MsgBox::Error(PTM_MSGBOX_TITLE, msg);
	}
	ptm_exit();
}
void ptm_update()
{
	ptm_refresh_window();
	ptm_proc_events();
}
void ptm_proc_events()
{
	SDL_Event e = { 0 };
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			ptm_exit();
			return;
		}
		else if (e.type == SDL_KEYDOWN) {
			const SDL_Keycode key = e.key.keysym.sym;
			if (key == SDLK_ESCAPE) {
				ptm_exit();
				return;
			}
			else if (key == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
				ptm_toggle_fullscreen();
				return;
			}
		}
	}
}
void ptm_idle_frame()
{
	ptm_update();
}
void ptm_show_message_box(string msg)
{
	MsgBox::Info(PTM_MSGBOX_TITLE, msg);
}
void ptm_on_exec_line(t_program_line* line, string& cmd, t_params& params)
{
	try {
		ptm_commands[cmd](params);
	}
	catch (bad_function_call ex) {
		ptm_abort("Invalid command");
	}

	if (!intp->errors.empty()) {
		ptm_abort(intp->errors[0]);
	}
}
void ptm_on_keydown(SDL_Keycode key)
{
	if (key == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
		ptm_toggle_fullscreen();
	}
	else if (key == SDLK_ESCAPE) {
		ptm_exit();
	}
}
