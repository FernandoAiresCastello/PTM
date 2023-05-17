#include "ptm_commands.h"
#include "ptm_core.h"
#include "ptm_graphics_base.h"

unordered_map<string, function<void(t_params&)>> ptm_commands;

#define CMD(x) ptm_commands[x] = [](t_params& arg)
#define ARG_STR(x) intp->require_string(arg[x])
#define ARG_NUM(x) intp->require_number(arg[x])
#define ARG_LABEL(x) intp->require_label(arg[x])
#define ARG_IDENT(x) intp->require_id(arg[x])
#define ARG_EXISTING_IDENT(x) intp->require_existing_varname(arg[x])
#define ARG_EXISTING_ARR(x) intp->require_existing_array(arg[x])
#define ARG_ARR_ELEMENT(x) intp->require_array_element(arg[x])

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
		string title = ARG_STR(0);
		ptm_set_window_title(title);
	};
	CMD("CLS") {
		ARGC(0);
		ptm_clear_screen();
	};
	CMD("WCOL") {
		ARGC(1);
		rgb bgcol = ARG_NUM(0);
		ptm_set_window_bgcol(bgcol);
	};
	CMD("DBG.BRK") {
		ARGC(0);
		debugger;
	};
	CMD("DBG.MSG") {
		ARGC(1);
		string msg = ARG_STR(0);
		ptm_show_message_box(msg);
	};
	CMD("PAUSE") {
		ARGC(1);
		int frames = ARG_NUM(0);
		for (int i = 0; i <= frames; i++) {
			ptm_idle_frame();
		}
	};
	CMD("GOTO") {
		ARGC(1);
		string label = ARG_LABEL(0);
		if (!label.empty()) {
			intp->goto_label(label);
		}
	};
	CMD("CALL") {
		ARGC(1);
		string label = ARG_LABEL(0);
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
		string dst_var = ARG_IDENT(0);
		if (!dst_var.empty()) {
			if (ptm_has_var(dst_var) && ptm_get_var(dst_var).is_const) {
				ptm_abort("Constant cannot be modified: " + dst_var);
				return;
			}
			if (arg[1].type == t_param_type::id) {
				string src_var = ARG_EXISTING_IDENT(1);
				if (!src_var.empty()) {
					ptm_copy_var(dst_var, src_var);
				}
			}
			else if (arg[1].is_array_element_ix()) {
				string value = ARG_ARR_ELEMENT(1);
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
		string dst_const = ARG_IDENT(0);
		if (!dst_const.empty()) {
			if (ptm_has_var(dst_const)) {
				ptm_abort("Identifier already in use: " + dst_const);
				return;
			}
			if (arg[1].type == t_param_type::id) {
				string src_var = ARG_EXISTING_IDENT(1);
				if (!src_var.empty()) {
					ptm_copy_var_to_const(dst_const, src_var);
				}
			}
			else {
				ptm_def_const(dst_const, arg[1].textual_value);
			}
		}
	};
	CMD("ARR.NEW") {
		ARGC_MIN_MAX(1, 2);
		string arr_id = ARG_IDENT(0);
		if (arr_id.empty()) return;
		int len = arg.size() == 1 ? 0 : ARG_NUM(1);
		ptm_new_array(arr_id, len);
	};
	CMD("ARR.PUSH") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arr_id.empty()) return;
		if (arg[1].type == t_param_type::char_literal) {
			ptm_array_push(arr_id, arg[1].numeric_value);
		}
		else {
			ptm_array_push(arr_id, arg[1].textual_value);
		}
	};
	CMD("ARR.LEN") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arr_id.empty()) return;
		string var_id = ARG_IDENT(1);
		if (var_id.empty()) return;
		ptm_set_var(var_id, ptm_array_size(arr_id));
	};
	CMD("ARR.SET") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arr_id.empty()) return;
		auto& arr = ptm_get_array(arr_id);
		int ix = intp->require_array_index(arr, arr_id, arg[0]);
		if (ix != PTM_INVALID_NUMBER) {
			arr[ix] = ARG_STR(1);
		}
	};
	CMD("ARR.ERASE") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arr_id.empty()) return;
		auto& arr = ptm_get_array(arr_id);
		int ix = ARG_NUM(1);
		if (ix != PTM_INVALID_NUMBER) {
			if (!arr.empty()) {
				if (ix < 0 || ix >= arr.size()) {
					intp->abort(String::Format("Array index out of bounds: %s[%i]", arr_id.c_str(), ix));
				}
				else {
					arr.erase(arr.begin() + ix);
				}
			}
			else {
				intp->abort("Array is empty: " + arr_id);
			}
		}
	};
	CMD("ARR.CLR") {
		ARGC(1);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arr_id.empty()) return;
		intp->arrays[arr_id].clear();
	};
	CMD("ARR.COPY") {
		ARGC(2);
		string src_arr_id = ARG_EXISTING_ARR(0);
		if (src_arr_id.empty()) return;
		string dst_arr_id = ARG_EXISTING_ARR(1);
		if (dst_arr_id.empty()) return;
		ptm_copy_array(dst_arr_id, src_arr_id);
	};
	CMD("ARR.FOR") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arr_id.empty()) return;
		string iter_var = ARG_IDENT(1);
		if (iter_var.empty()) return;
		intp->array_loop_start(arr_id, iter_var);
	};
	CMD("FOR") {
		ARGC_MIN_MAX(3, 4);
		string id = ARG_IDENT(0);
		if (id.empty()) return;
		int first = ARG_NUM(1);
		if (first == PTM_INVALID_NUMBER) return;
		int last = ARG_NUM(2);
		if (last == PTM_INVALID_NUMBER) return;
		int step = arg.size() == 4 ? ARG_NUM(3) : 1;
		if (step == PTM_INVALID_NUMBER) return;
		intp->loop_start(id, first, last, step);
	};
	CMD("NEXT") {
		ARGC(0);
		intp->loop_end();
	};
	CMD("BRK") {
		ARGC(0);
		intp->loop_break();
	};
	CMD("SKIP") {
		ARGC(0);
		intp->loop_continue();
	};
	CMD("IF.EQ") {
		ARGC(2);
		ptm_if_block_start(arg, CMP_MODE_EQ);
	};
	CMD("IF.NEQ") {
		ARGC(2);
		ptm_if_block_start(arg, CMP_MODE_NEQ);
	};
	CMD("IF.GT") {
		ARGC(2);
		ptm_if_block_start(arg, CMP_MODE_GT);
	};
	CMD("IF.GTE") {
		ARGC(2);
		ptm_if_block_start(arg, CMP_MODE_GTE);
	};
	CMD("IF.LT") {
		ARGC(2);
		ptm_if_block_start(arg, CMP_MODE_LT);
	};
	CMD("IF.LTE") {
		ARGC(2);
		ptm_if_block_start(arg, CMP_MODE_LTE);
	};
	CMD("ENDIF") {
		ARGC(0);
	};
	CMD("IF.GOTO") {
		ARGC(3);
		string a = ARG_STR(0);
		string b = ARG_STR(1);
		string label = ARG_LABEL(2);
		if (label.empty()) return;
		if (a == b) {
			intp->goto_label(label);
		}
	};
	CMD("IF.CALL") {
		ARGC(3);
		string a = ARG_STR(0);
		string b = ARG_STR(1);
		string label = ARG_LABEL(2);
		if (label.empty()) return;
		if (a == b) {
			intp->call_label(label);
		}
	};
	CMD("IF.KEY") {
		ARGC(1);
		string keyname = intp->require_string(arg[0]);
		if (keyname.empty()) return;
		if (!ptm_last_key(keyname)) {
			intp->goto_matching_endif();
		}
	};
	CMD("INC") {
		ARGC(1);
		string id = ARG_IDENT(0);
		if (id.empty()) return;
		auto& var = ptm_get_var(id);
		ptm_set_var(id, String::ToInt(var.value) + 1);
	};
	CMD("DEC") {
		ARGC(1);
		string id = ARG_IDENT(0);
		if (id.empty()) return;
		auto& var = ptm_get_var(id);
		ptm_set_var(id, String::ToInt(var.value) - 1);
	};
	CMD("FRAMES") {
		ARGC(1);
		string id = ARG_IDENT(0);
		if (id.empty()) return;
		ptm_set_var(id, scr.frame_counter);
	};
}
