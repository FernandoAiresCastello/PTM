#include "ptm_commands.h"
#include "ptm_core.h"
#include "ptm_graphics_base.h"
#include "ptm_tile_system.h"
#include "ptm_color_palette.h"
#include "ptm_sound_system.h"

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
	CMD("TEST") {
	};
	CMD("INCL") {
		// t_program.cpp
	};
	CMD("DATA") {
		// t_compiler.cpp
	};
	CMD("WINDOW") {
		// t_compiler.cpp
	};
	CMD("ASSERT") {
		ARGC(2);
		string x_var = arg[0].src;
		string x_value = ARG_STR(0);
		string y_var = arg[1].src;
		string y_value = ARG_STR(1);
		if (x_value != y_value) {
			ptm_abort(String::Format("Assertion error\n\n%s = %s\n%s = %s", 
				x_var.c_str(), x_value.c_str(), y_var.c_str(), y_value.c_str()));
		}
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
		ARGC(1);
		int palette_ix = ARG_NUM(0);
		ptm_set_window_bgcol(palette.get(palette_ix));
		ptm_clear_screen();
	};
	CMD("ANIM") {
		ARGC(1);
		int speed = ARG_NUM(0);
		ptm_set_tile_animation_speed(speed);
	};
	CMD("DEBUG") {
		ARGC(0);
		debugger;
	};
	CMD("MSGBOX") {
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
		intp->goto_label(label);
	};
	CMD("CALL") {
		ARGC(1);
		string label = ARG_LABEL(0);
		intp->call_label(label);
	};
	CMD("RET") {
		ARGC(0);
		intp->return_from_call();
	};
	CMD("VAR") {
		ARGC(2);
		string dst_var = ARG_IDENT(0);
		if (ptm_has_var(dst_var) && ptm_get_var(dst_var).is_const) {
			ptm_abort("Constant cannot be modified: " + dst_var);
			return;
		}
		if (arg[1].type == t_param_type::id) {
			string src_var = ARG_EXISTING_IDENT(1);
			ptm_copy_var(dst_var, src_var);
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
	};
	CMD("DEF") {
		ARGC(2);
		string dst_const = ARG_IDENT(0);
		if (ptm_has_var(dst_const)) {
			ptm_abort("Identifier already in use: " + dst_const);
			return;
		}
		if (arg[1].type == t_param_type::id) {
			string src_var = ARG_EXISTING_IDENT(1);
			ptm_copy_var_to_const(dst_const, src_var);
		}
		else {
			ptm_def_const(dst_const, arg[1].textual_value);
		}
	};
	CMD("ARR.NEW") {
		ARGC_MIN_MAX(1, 2);
		string arr_id = ARG_IDENT(0);
		int len = arg.size() == 1 ? 0 : ARG_NUM(1);
		ptm_new_array(arr_id, len);
	};
	CMD("ARR.PUSH") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		if (arg[1].type == t_param_type::char_literal) {
			ptm_array_push(arr_id, arg[1].numeric_value);
		}
		else if (arg[1].type == t_param_type::id) {
			ptm_array_push(arr_id, ptm_get_var(arg[1].id).value);
		}
		else {
			ptm_array_push(arr_id, arg[1].textual_value);
		}
	};
	CMD("ARR.LEN") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		string var_id = ARG_IDENT(1);
		ptm_set_var(var_id, ptm_array_size(arr_id));
	};
	CMD("ARR.SET") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		auto& arr = ptm_get_array(arr_id);
		int ix = intp->require_array_index(arr, arr_id, arg[0]);
		arr[ix] = ARG_STR(1);
	};
	CMD("ARR.ERASE") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		auto& arr = ptm_get_array(arr_id);
		int ix = ARG_NUM(1);
		if (!arr.empty()) {
			if (ix < 0 || ix >= arr.size()) {
				ptm_abort(String::Format("Array index out of bounds: %s[%i]", arr_id.c_str(), ix));
			}
			else {
				arr.erase(arr.begin() + ix);
			}
		}
		else {
			ptm_abort("Array is empty: " + arr_id);
		}
	};
	CMD("ARR.CLR") {
		ARGC(1);
		string arr_id = ARG_EXISTING_ARR(0);
		intp->arrays[arr_id].clear();
	};
	CMD("ARR.COPY") {
		ARGC(2);
		string src_arr_id = ARG_EXISTING_ARR(0);
		string dst_arr_id = ARG_EXISTING_ARR(1);
		ptm_copy_array(dst_arr_id, src_arr_id);
	};
	CMD("ARR.FOR") {
		ARGC(2);
		string arr_id = ARG_EXISTING_ARR(0);
		string iter_var = ARG_IDENT(1);
		intp->array_loop_start(arr_id, iter_var);
	};
	CMD("FOR") {
		ARGC_MIN_MAX(3, 4);
		string id = ARG_IDENT(0);
		int first = ARG_NUM(1);
		int last = ARG_NUM(2);
		int step = arg.size() == 4 ? ARG_NUM(3) : 1;
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
		if (a == b) {
			intp->goto_label(label);
		}
	};
	CMD("IF.CALL") {
		ARGC(3);
		string a = ARG_STR(0);
		string b = ARG_STR(1);
		string label = ARG_LABEL(2);
		if (a == b) {
			intp->call_label(label);
		}
	};
	CMD("IF.KEY") {
		ARGC(1);
		string keyname = ARG_STR(0);
		if (!ptm_last_key(keyname)) {
			intp->goto_matching_endif();
		}
	};
	CMD("INC") {
		ARGC(1);
		string id = ARG_IDENT(0);
		auto& var = ptm_get_var(id);
		ptm_set_var(id, String::ToInt(var.value) + 1);
	};
	CMD("DEC") {
		ARGC(1);
		string id = ARG_IDENT(0);
		auto& var = ptm_get_var(id);
		ptm_set_var(id, String::ToInt(var.value) - 1);
	};
	CMD("FRAMES") {
		ARGC(1);
		string id = ARG_IDENT(0);
		ptm_set_var(id, scr.frame_counter);
	};
	CMD("CHR") {
		ARGC(2);
		int ix = ARG_NUM(0);
		binary bin = ARG_STR(1);
		tileset.set(ix, bin);
	};
	CMD("PAL") {
		ARGC(2);
		int ix = ARG_NUM(0);
		rgb color = ARG_NUM(1);
		palette.set(ix, color);
	};
	CMD("BUF.NEW") {
		ARGC(4);
		string id = ARG_STR(0);
		int layers = ARG_NUM(1);
		int width = ARG_NUM(2);
		int height = ARG_NUM(3);
		if (tilebufs.has(id)) {
			ptm_abort("Duplicate buffer id: " + id);
		}
		else {
			tilebufs.new_tilebuf(id, layers, width, height);
		}
	};
	CMD("BUF.VIEW") {
		ARGC(5);
		string id = ARG_STR(0);
		int x1 = ARG_NUM(1);
		int y1 = ARG_NUM(2);
		int x2 = ARG_NUM(3);
		int y2 = ARG_NUM(4);
		tilebufs.get(id).view(x1, y1, x2, y2);
	};
	CMD("BUF.SCRL") {
		ARGC(3);
		string id = ARG_STR(0);
		int dx = ARG_NUM(1);
		int dy = ARG_NUM(2);
		tilebufs.get(id).scroll_view(dx, dy);
	};
	CMD("BUF.SHOW") {
		ARGC(1);
		string id = ARG_STR(0);
		tilebufs.get(id).show();
	};
	CMD("BUF.HIDE") {
		ARGC(1);
		string id = ARG_STR(0);
		tilebufs.get(id).hide();
	};
	CMD("BUF.BCOL") {
		ARGC(2);
		string id = ARG_STR(0);
		int palette_ix = ARG_NUM(1);
		tilebufs.get(id).set_bgcol(palette_ix);
	};
	CMD("BUF.SEL") {
		ARGC(1);
		string id = ARG_STR(0);
		if (tilebufs.has(id)) {
			tilebufs.select(id);
		}
		else {
			ptm_abort("Tilebuffer not found: " + id);
		}
	};
	CMD("TILE.NEW") {
		ARGC(3);
		int ch = ARG_NUM(0);
		int fgc = ARG_NUM(1);
		int bgc = ARG_NUM(2);
		working_tile.clear();
		working_tile.add(ch, fgc, bgc);
	};
	CMD("TILE.ADD") {
		ARGC(3);
		int ch = ARG_NUM(0);
		int fgc = ARG_NUM(1);
		int bgc = ARG_NUM(2);
		working_tile.add(ch, fgc, bgc);
	};
	CMD("TILE.SETC") {
		ARGC(2);
		int ix = ARG_NUM(0);
		int ch = ARG_NUM(1);
		working_tile.set_ch(ix, ch);
	};
	CMD("TILE.SETF") {
		ARGC(2);
		int ix = ARG_NUM(0);
		int fgc = ARG_NUM(1);
		working_tile.set_fgc(ix, fgc);
	};
	CMD("TILE.SETB") {
		ARGC(2);
		int ix = ARG_NUM(0);
		int bgc = ARG_NUM(1);
		working_tile.set_bgc(ix, bgc);
	};
	CMD("TILE.GETC") {
		ARGC(2);
		int ix = ARG_NUM(0);
		string var = ARG_IDENT(1);
		ptm_set_var(var, working_tile.frames[ix].ch);
	};
	CMD("TILE.GETF") {
		ARGC(2);
		int ix = ARG_NUM(0);
		string var = ARG_IDENT(1);
		ptm_set_var(var, working_tile.frames[ix].fgc);
	};
	CMD("TILE.GETB") {
		ARGC(2);
		int ix = ARG_NUM(0);
		string var = ARG_IDENT(1);
		ptm_set_var(var, working_tile.frames[ix].bgc);
	};
	CMD("TILE.COLOR") {
		ARGC(3);
		int ix = ARG_NUM(0);
		int fgc = ARG_NUM(1);
		int bgc = ARG_NUM(2);
		working_tile.set_fgc(ix, fgc);
		working_tile.set_bgc(ix, bgc);
	};
	CMD("TILE.LEN") {
		ARGC(1);
		string var = ARG_IDENT(0);
		ptm_set_var(var, working_tile.length());
	};
	CMD("TILE.PARSE") {
		ARGC(1);
		string str = ARG_STR(0);
		bool ok = working_tile.parse(str);
		if (!ok) {
			ptm_abort("Could not parse tile definition: " + str);
		}
	};
	CMD("TILE.STR") {
		ARGC(1);
		string var = ARG_IDENT(0);
		ptm_set_var(var, working_tile.to_str());
	};
	CMD("TILE.STORE") {
		ARGC(1);
	};
	CMD("TILE.LOAD") {
		ARGC(1);
	};
	CMD("TILE.SETP") {
		ARGC(2);
	};
	CMD("TILE.GETP") {
		ARGC(2);
	};
	CMD("LAYER") {
		ARGC(1);
		int layer = ARG_NUM(0);
		if (layer < 0 || layer >= tilebufs.selected()->get_layer_count()) {
			ptm_abort("Invalid layer for selected buffer: " + tilebufs.selected_id());
		}
		tilebuf_csr.layer = layer;
	};
	CMD("LOCATE") {
		ARGC(2);
		int x = ARG_NUM(0);
		int y = ARG_NUM(1);
		tilebuf_csr.x = x;
		tilebuf_csr.y = y;
	};
	CMD("PUT") {
		ARGC(0);
		ptm_get_selected_tilebuf_layer().put(tilebuf_csr.x, tilebuf_csr.y, working_tile);
	};
	CMD("DEL") {
		ARGC(0);
		ptm_get_selected_tilebuf_layer().del(tilebuf_csr.x, tilebuf_csr.y);
	};
	CMD("GET") {
		ARGC(0);
		working_tile.set_equal(
			ptm_get_selected_tilebuf_layer().get(tilebuf_csr.x, tilebuf_csr.y));
	};
	CMD("FILL") {
		ARGC(0);
		ptm_get_selected_tilebuf_layer().fill(working_tile);
	};
	CMD("PRINT") {
		ARGC(1);
		string str = ARG_STR(0);
		ptm_print_tile_string(str);
	};
	CMD("FCOL") {
		ARGC(1);
		int fgc = ARG_NUM(0);
		scr.text_style.fgc = fgc;
	};
	CMD("BCOL") {
		ARGC(1);
		int bgc = ARG_NUM(0);
		scr.text_style.bgc = bgc;
	};
	CMD("COLOR") {
		ARGC(2);
		int fgc = ARG_NUM(0);
		int bgc = ARG_NUM(1);
		scr.text_style.fgc = fgc;
		scr.text_style.bgc = bgc;
	};
	CMD("SND.LOAD") {
		ARGC(2);
		string id = ARG_STR(0);
		string file = ARG_STR(1);
		ptm_load_sound_wav(id, file);
	};
	CMD("SND.PLAY") {
		ARGC(1);
		string id = ARG_STR(0);
		ptm_play_sound_wav(id);
	};
	CMD("SND.STOP") {
		ARGC(0);
		ptm_stop_all_sounds();
	};
}
