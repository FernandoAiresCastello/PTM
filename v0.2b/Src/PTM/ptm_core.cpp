#include "ptm_core.h"
#include "ptm_commands.h"
#include "ptm_utils.h"
#include "../PTML/t_program.h"
#include "../PTML/t_compiler.h"
#include "../PTML/t_interpreter.h"

t_interpreter* intp = nullptr;

struct {
	struct {
		bool initialized = false;
		SDL_Window* wnd = nullptr;
		SDL_Renderer* rend = nullptr;
		SDL_Texture* tx = nullptr;
		rgb* pixel_buf = nullptr;
		int buf_w = 256;
		int buf_h = 192;
		int buf_len = buf_w * buf_h;
		int wnd_size = 4;
		rgb bgcol = 0x101010;
		int frame_counter = 0;
	} scr;
} ptm;

void ptm_run(string program_file)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	ptm_init_commands();
	ptm.scr.initialized = false;

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
	if (!ptm.scr.initialized)
		return;

	static int pitch;
	static void* pixels;
	
	SDL_LockTexture(ptm.scr.tx, NULL, &pixels, &pitch);
	SDL_memcpy(pixels, ptm.scr.pixel_buf, ptm.scr.buf_len * sizeof(rgb));
	SDL_UnlockTexture(ptm.scr.tx);
	SDL_RenderClear(ptm.scr.rend);
	SDL_RenderCopy(ptm.scr.rend, ptm.scr.tx, NULL, NULL);
	SDL_RenderPresent(ptm.scr.rend);

	ptm.scr.frame_counter++;
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
void ptm_clear_screen()
{
	SDL_memset4(ptm.scr.pixel_buf, ptm.scr.bgcol, ptm.scr.buf_len);
}
void ptm_toggle_fullscreen()
{
	Uint32 flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	Uint32 is_full = SDL_GetWindowFlags(ptm.scr.wnd) & flag;
	SDL_SetWindowFullscreen(ptm.scr.wnd, is_full ? 0 : flag);
	ptm_update();
}
void ptm_init_window(int buf_w, int buf_h, int size, rgb bgcol)
{
	ptm.scr.initialized = true;
	ptm.scr.buf_w = buf_w;
	ptm.scr.buf_h = buf_h;
	ptm.scr.buf_len = buf_w * buf_h;
	ptm.scr.wnd_size = size;
	ptm.scr.bgcol = bgcol;

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	ptm.scr.pixel_buf = new rgb[ptm.scr.buf_len];
	ptm.scr.wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		ptm.scr.wnd_size * ptm.scr.buf_w, ptm.scr.wnd_size * ptm.scr.buf_h, 0);
	ptm.scr.rend = SDL_CreateRenderer(ptm.scr.wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetLogicalSize(ptm.scr.rend, ptm.scr.buf_w, ptm.scr.buf_h);
	ptm.scr.tx = SDL_CreateTexture(ptm.scr.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, ptm.scr.buf_w, ptm.scr.buf_h);
	SDL_SetTextureBlendMode(ptm.scr.tx, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawBlendMode(ptm.scr.rend, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(ptm.scr.rend, 0, 0, 0, 255);
	SDL_RenderClear(ptm.scr.rend);
	SDL_RenderPresent(ptm.scr.rend);
	ptm_clear_screen();
	ptm_update();
	SDL_SetWindowPosition(ptm.scr.wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_RaiseWindow(ptm.scr.wnd);
}
void ptm_free_window()
{
	delete ptm.scr.pixel_buf;           ptm.scr.pixel_buf = nullptr;
	SDL_DestroyTexture(ptm.scr.tx);     ptm.scr.tx = nullptr;
	SDL_DestroyRenderer(ptm.scr.rend);  ptm.scr.rend = nullptr;
	SDL_DestroyWindow(ptm.scr.wnd);     ptm.scr.wnd = nullptr;
}
void ptm_set_window_title(string title)
{
	SDL_SetWindowTitle(ptm.scr.wnd, title.c_str());
}
void ptm_set_window_bgcol(rgb bgcol)
{
	ptm.scr.bgcol = bgcol;
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
