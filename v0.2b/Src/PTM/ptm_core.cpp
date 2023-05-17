#include "ptm_core.h"
#include "ptm_commands.h"
#include "ptm_graphics_base.h"
#include "ptm_keyboard.h"
#include "../PTML/t_program.h"
#include "../PTML/t_compiler.h"
#include "../PTML/t_interpreter.h"

t_interpreter* intp = nullptr;
t_compiler* compiler = nullptr;

void ptm_abort_from_compiler();
void ptm_abort_from_interpreter();

void ptm_run(string program_file)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	ptm_init_commands();
	ptm_init_keyboard();

	t_program* prg = new t_program();
	if (!prg->load_plain(program_file)) {
		delete prg;     prg = nullptr;
		return;
	}
	compiler = new t_compiler();
	compiler->run(prg);
	if (!compiler->errors.empty()) {
		ptm_abort_from_compiler();
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
	intp->on_abort = ptm_abort_from_interpreter;
	intp->run(prg);

	delete intp;    intp = nullptr;
	delete prg;     prg = nullptr;
}
void ptm_abort(string msg)
{
	intp->abort(msg);
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
void ptm_abort_from_compiler()
{
	MsgBox::Error(PTM_MSGBOX_TITLE, compiler->errors[0]);
	ptm_exit();
}
void ptm_abort_from_interpreter()
{
	MsgBox::Error(PTM_MSGBOX_TITLE, intp->errors[0]);
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
			last_key = key;
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
		intp->abort("Command not found");
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
bool ptm_has_var(string name)
{
	return intp->vars.find(name) != intp->vars.end();
}
void ptm_set_var(string name, string value)
{
	intp->vars[name] = t_variable(value, false);
}
void ptm_set_var(string name, int value)
{
	intp->vars[name] = t_variable(value, false);
}
t_variable& ptm_get_var(string name)
{
	return intp->vars[name];
}
void ptm_copy_var(string dst, string src)
{
	intp->vars[dst] = intp->vars[src];
	intp->vars[dst].is_const = false;
}
void ptm_copy_var_to_const(string dst, string src)
{
	intp->vars[dst] = intp->vars[src];
	intp->vars[dst].is_const = true;
}
void ptm_def_const(string name, string value)
{
	intp->vars[name] = t_variable(value, true);
}
void ptm_def_const(string name, int value)
{
	intp->vars[name] = t_variable(value, true);
}
void ptm_new_array(string name, int size)
{
	if (size >= 0) {
		intp->arrays[name] = std::vector<string>();
		for (int i = 0; i < size; i++) {
			intp->arrays[name].push_back("");
		}
	}
	else {
		intp->abort("Illegal array length");
	}
}
void ptm_array_push(string name, string value)
{
	intp->arrays[name].push_back(value);
}
void ptm_array_push(string name, int value)
{
	intp->arrays[name].push_back(String::ToString(value));
}
int ptm_array_size(string name)
{
	return intp->arrays[name].size();
}
vector<string>& ptm_get_array(string name)
{
	return intp->arrays[name];
}
void ptm_copy_array(string dst, string src)
{
	intp->arrays[dst] = intp->arrays[src];
}
void ptm_if_block_start(t_params& arg, int cmp_mode)
{
	if (cmp_mode == CMP_MODE_EQ || cmp_mode == CMP_MODE_NEQ) {
		string a = intp->require_string(arg[0]);
		string b = intp->require_string(arg[1]);
		if (cmp_mode == CMP_MODE_EQ) {
			if (a == b) { return; }
			else { intp->goto_matching_endif(); }
		}
		else if (cmp_mode == CMP_MODE_NEQ) {
			if (a != b) { return; }
			else { intp->goto_matching_endif(); }
		}
	}
	else {
		int a = intp->require_number(arg[0]);
		if (a == PTM_INVALID_NUMBER) return;
		int b = intp->require_number(arg[1]);
		if (b == PTM_INVALID_NUMBER) return;

		if (cmp_mode == CMP_MODE_GT) {
			if (a > b) { return; }
			else { intp->goto_matching_endif(); }
		}
		else if (cmp_mode == CMP_MODE_GTE) {
			if (a >= b) { return; }
			else { intp->goto_matching_endif(); }
		}
		else if (cmp_mode == CMP_MODE_LT) {
			if (a < b) { return; }
			else { intp->goto_matching_endif(); }
		}
		else if (cmp_mode == CMP_MODE_LTE) {
			if (a <= b) { return; }
			else { intp->goto_matching_endif(); }
		}
	}
}
bool ptm_last_key(string keyname)
{
	keyname = String::ToUpper(keyname);

	if (keyname == "SHIFT") return ptm_kb_shift();
	if (keyname == "CTRL") return ptm_kb_ctrl();
	if (keyname == "ALT") return ptm_kb_alt();
	if (keyname == "CAPS") return ptm_kb_caps();

	return ptm_kb_pressed(keyname);
}
