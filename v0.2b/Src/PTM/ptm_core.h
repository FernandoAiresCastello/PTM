#pragma once
#include "../Common/common.h"
#include "../PTML/t_interpreter.h"
#include "../PTML/t_program_line.h"
#include "../PTML/t_param.h"

extern t_interpreter* intp;

void ptm_run(string program_file);
void ptm_abort(string msg);
void ptm_exit();
void ptm_halt();
void ptm_update();
void ptm_proc_events();
void ptm_idle_frame();
void ptm_show_message_box(string msg);
void ptm_on_exec_line(t_program_line* line, string& cmd, t_params& params);
void ptm_on_keydown(SDL_Keycode key);
bool ptm_has_var(string name);
void ptm_set_var(string name, string value);
void ptm_set_var(string name, int value);
t_variable& ptm_get_var(string name);
void ptm_copy_var(string dst, string src);
void ptm_copy_var_to_const(string dst, string src);
void ptm_def_const(string name, string value);
void ptm_def_const(string name, int value);
void ptm_new_array(string name, int size);
void ptm_array_push(string name, string value);
void ptm_array_push(string name, int value);
int ptm_array_size(string name);
vector<string>& ptm_get_array(string name);
void ptm_copy_array(string dst, string src);
void ptm_if_block_start(t_params& arg, int cmp_mode);
void ptm_if_block_end();
