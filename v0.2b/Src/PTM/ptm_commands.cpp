#include "ptm_commands.h"
#include "ptm_core.h"
#include "ptm_graphics_base.h"

#define CMD(x) ptm_commands[x] = [](t_params& arg)
#define STR(x) intp->require_string(arg[x])
#define NUM(x) intp->require_number(arg[x])
#define LBL(x) intp->require_label(arg[x])

unordered_map<string, function<void(t_params&)>> ptm_commands;

void ptm_init_commands()
{
	// Compile-time commands
	
	CMD("INCL") {};
	CMD("DATA") {};
	CMD("WINDOW") {};

	// Run-time commands

	CMD("TEST") {
	};
	CMD("EXIT") {
		ARGC(0);
		ptm_exit();
	};
	CMD("HALT") {
		ARGC(0);
		ptm_halt();
	};
	CMD("UPDATE") {
		ARGC(0);
		ptm_update();
	};
	CMD("TITLE") {
		ARGC(1);
		string title = STR(0);
		ptm_set_window_title(title);
	};
	CMD("CLS") {
		ARGC(0);
		ptm_clear_screen();
	};
	CMD("WCOL") {
		ARGC(1);
		rgb bgcol = NUM(0);
		ptm_set_window_bgcol(bgcol);
	};
	CMD("DBG.BRK") {
		ARGC(0);
		debugger;
	};
	CMD("DBG.MSG") {
		ARGC(1);
		string msg = STR(0);
		ptm_show_message_box(msg);
	};
	CMD("PAUSE") {
		ARGC(1);
		int frames = NUM(0);
		for (int i = 0; i <= frames; i++) {
			ptm_idle_frame();
		}
	};
	CMD("GOTO") {
		ARGC(1);
		string label = LBL(0);
		if (!label.empty()) {
			intp->goto_label(label);
		}
	};
	CMD("CALL") {
		ARGC(1);
		string label = LBL(0);
		if (!label.empty()) {
			intp->call_label(label);
		}
	};
	CMD("RET") {
		ARGC(0);
		intp->return_from_call();
	};
	CMD("VAR") {
		ARGC(2);
		string dst_var = intp->require_id(arg[0]);
		if (!dst_var.empty()) {
			if (ptm_has_var(dst_var) && ptm_get_var(dst_var).is_const) {
				intp->abort("Constant cannot be modified: " + dst_var);
				return;
			}
			if (arg[1].type == t_param_type::id) {
				string src_var = intp->require_existing_varname(arg[1]);
				if (!src_var.empty()) {
					ptm_copy_var(dst_var, src_var);
				}
			}
			else if (arg[1].is_array_element_ix()) {
				string value = intp->require_array_element(arg[1]);
				ptm_set_var(dst_var, value);
			}
			else if (arg[1].type == t_param_type::char_literal) {
				ptm_set_var(dst_var, arg[1].numeric_value);
			}
			else {
				ptm_set_var(dst_var, arg[1].textual_value);
			}
		}
	};
	CMD("DEF") {
		ARGC(2);
		string dst_const = intp->require_id(arg[0]);
		if (!dst_const.empty()) {
			if (ptm_has_var(dst_const)) {
				intp->abort("Identifier already in use: " + dst_const);
				return;
			}
			if (arg[1].type == t_param_type::id) {
				string src_var = intp->require_existing_varname(arg[1]);
				if (!src_var.empty()) {
					ptm_copy_var_to_const(dst_const, src_var);
				}
			}
			else {
				ptm_def_const(dst_const, arg[1].textual_value);
			}
		}
	};
}
