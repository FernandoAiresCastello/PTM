#pragma once
#include "common.h"
#include "Compiler/t_interpreter.h"
#include "Compiler/t_program_line.h"
#include "Compiler/t_param.h"

extern t_interpreter* intp;

void ptm_run(string program_file);
void ptm_exit();
void ptm_halt();
void ptm_abort(string msg = "");
void ptm_update();
void ptm_proc_events();
void ptm_clear_screen();
void ptm_wnd_bgcol(rgb color);
void ptm_toggle_fullscreen();
void ptm_init_window(int buf_w, int buf_h, int size, rgb bgcol);
void ptm_free_window();
void ptm_on_exec_line(t_program_line* line, string& cmd, t_params& params);
void ptm_on_keydown(SDL_Keycode key);
void ptm_on_idle_loop();
