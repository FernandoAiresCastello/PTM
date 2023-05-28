#pragma once

#include <functional>
#include "../PTML/t_param.h"
#include "ptm_core.h"
#include "ptm_graphics_base.h"
#include "ptm_tile_system.h"
#include "ptm_color_palette.h"
#include "ptm_sound_system.h"
#include "ptm_sprites.h"
#include "ptm_filesystem.h"
#include "ptm_keyboard.h"
#include "ptm_mml.h"

#define CMD(x) ptm_commands[x] = [](t_params& arg)
#define ARG_VAR_STR(x) intp->arg_var_string(arg[x])
#define ARG_VAR_NUM(x) intp->arg_var_number(arg[x])
#define ARG_LIT_LABEL(x) intp->arg_literal_existing_label(arg[x])
#define ARG_LIT_ID(x) intp->arg_literal_id(arg[x])
#define ARG_LIT_ID_EXISTING(x) intp->arg_literal_existing_id(arg[x])
#define ARG_LIT_ARR_ID(x) intp->arg_literal_array_id(arg[x])
#define ARG_ARR_STR(x) intp->arg_string_from_array_element(arg[x])

extern unordered_map<string, function<void(t_params&)>> ptm_commands;

enum {
	CMP_MODE_EQ, CMP_MODE_NEQ,
	CMP_MODE_GT, CMP_MODE_GTE,
	CMP_MODE_LT, CMP_MODE_LTE,
	CMP_MODE_TRUE, CMP_MODE_FALSE
};

void ptm_init_commands();
