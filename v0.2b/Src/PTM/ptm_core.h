#pragma once
#include "../Common/common.h"
#include "../PTML/t_interpreter.h"
#include "../PTML/t_program_line.h"
#include "../PTML/t_param.h"

extern t_program* prg;
extern t_interpreter* intp;
extern const char xor_encryption_key;

int ptm_run(string program_file);
void ptm_save_encrypted_program(t_program* prg, string dest_file);
void ptm_abort(string msg);
void ptm_exit();
void ptm_delete_interpreter();
void ptm_reset();
void ptm_halt();
void ptm_update();
void ptm_proc_events();
void ptm_idle_frame();
void ptm_show_message_box(string msg);
void ptm_on_exec_line(t_program_line* line, string& cmd, t_params& params);
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
int ptm_get_random_number(int min, int max);
string ptm_sprintf(string fmt);
void ptm_launch_new_instance_with_program(string program_path);
void ptm_clipboard_set(string value);
string ptm_clipboard_get();
void ptm_save_debug_file(string file);
