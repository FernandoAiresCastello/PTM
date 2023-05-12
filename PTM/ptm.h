#pragma once
#include "common.h"
#include "Compiler/t_param.h"

void ptm_init(string program_file);
void ptm_exit();
void ptm_halt();
void ptm_abort(string msg = "");
void ptm_update();
void ptm_proc_events();
void ptm_clear_screen();
void ptm_wnd_bgcol(rgb color);
void ptm_toggle_fullscreen();
void ptm_load_program(string path);
void ptm_init_window();
void ptm_free_window();
void ptm_on_loop();
void ptm_on_loop_idle();
void ptm_on_keydown(SDL_Keycode key);
void ptm_on_exec_line(string& cmd, t_params& params);
