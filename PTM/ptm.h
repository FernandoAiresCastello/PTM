#pragma once
#include "includes.h"

//=============================================================================
//      PUBLIC API
//=============================================================================
void ptm_init(string program_file);
void ptm_exit();
void ptm_halt();
void ptm_abort(string msg);
void ptm_update();
void ptm_proc_events();
void ptm_poke(addr address, int value);
void ptm_clear_screen();
void ptm_wnd_bgcol(rgb color);
void ptm_toggle_fullscreen();

//=============================================================================
//      PRIVATE API
//=============================================================================
void ptm_load_program(string path);
void ptm_init_window();
void ptm_free_window();
void ptm_init_memory();
