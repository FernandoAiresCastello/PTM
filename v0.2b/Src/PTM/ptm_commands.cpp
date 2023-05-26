#include "ptm_commands.h"
#include "ptm_core.h"
#include "ptm_graphics_base.h"
#include "ptm_tile_system.h"
#include "ptm_color_palette.h"
#include "ptm_sound_system.h"
#include "ptm_sprites.h"
#include "ptm_filesystem.h"
#include "ptm_keyboard.h"
#include "ptm_mml.h"

unordered_map<string, function<void(t_params&)>> ptm_commands;

#define CMD(x) ptm_commands[x] = [](t_params& arg)
#define ARG_VAR_STR(x) intp->arg_var_string(arg[x])
#define ARG_VAR_NUM(x) intp->arg_var_number(arg[x])
#define ARG_LIT_LABEL(x) intp->arg_literal_existing_label(arg[x])
#define ARG_LIT_ID(x) intp->arg_literal_id(arg[x])
#define ARG_LIT_ID_EXISTING(x) intp->arg_literal_existing_id(arg[x])
#define ARG_LIT_ARR_ID(x) intp->arg_literal_array_id(arg[x])
#define ARG_ARR_STR(x) intp->arg_string_from_array_element(arg[x])

void ptm_init_commands()
{
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
		string x_value = ARG_VAR_STR(0);
		string y_var = arg[1].src;
		string y_value = ARG_VAR_STR(1);
		if (x_value != y_value) {
			ptm_abort(String::Format("Assertion error\n\n%s = %s\n%s = %s", 
				x_var.c_str(), x_value.c_str(), y_var.c_str(), y_value.c_str()));
		}
	};
	CMD("EXIT") {
		ARGC(0);
		ptm_exit();
	};
	CMD("RESET") {
		ARGC(0);
		ptm_reset();
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
		string title = ARG_VAR_STR(0);
		ptm_set_window_title(title);
	};
	CMD("WCOL") {
		ARGC(1);
		int palette_ix = ARG_VAR_NUM(0);
		ptm_set_window_bgcol(palette.get(palette_ix));
		ptm_clear_screen();
	};
	CMD("TRON") {
		ARGC(0);
		scr.transparency = true;
	};
	CMD("TROFF") {
		ARGC(0);
		scr.transparency = false;
	};
	CMD("ANIM") {
		ARGC(1);
		int speed = ARG_VAR_NUM(0);
		ptm_set_tile_animation_speed(speed);
	};
	CMD("DEBUG") {
		ARGC(0);
		debugger;
	};
	CMD("MSGBOX") {
		ARGC(1);
		string msg = ARG_VAR_STR(0);
		ptm_show_message_box(msg);
	};
	CMD("PAUSE") {
		ARGC(1);
		int frames = ARG_VAR_NUM(0);
		for (int i = 0; i <= frames; i++) {
			ptm_idle_frame();
		}
	};
	CMD("GOTO") {
		ARGC(1);
		string label = ARG_LIT_LABEL(0);
		intp->goto_label(label);
	};
	CMD("CALL") {
		ARGC(1);
		string label = ARG_LIT_LABEL(0);
		intp->call_label(label);
	};
	CMD("RET") {
		ARGC(0);
		intp->return_from_call();
	};
	CMD("VAR") {
		ARGC(2);
		string dst_var = ARG_LIT_ID(0);
		if (ptm_has_var(dst_var) && ptm_get_var(dst_var).is_const) {
			ptm_abort("Constant cannot be modified: " + dst_var);
			return;
		}
		if (arg[1].type == t_param_type::id) {
			string src_var = ARG_LIT_ID_EXISTING(1);
			ptm_copy_var(dst_var, src_var);
		}
		else if (arg[1].is_array_element_ix()) {
			string value = ARG_ARR_STR(1);
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
		string dst_const = ARG_LIT_ID(0);
		if (ptm_has_var(dst_const)) {
			ptm_abort("Identifier already in use: " + dst_const);
			return;
		}
		if (arg[1].type == t_param_type::id) {
			string src_var = ARG_LIT_ID_EXISTING(1);
			ptm_copy_var_to_const(dst_const, src_var);
		}
		else {
			ptm_def_const(dst_const, arg[1].textual_value);
		}
	};
	CMD("ARR.NEW") {
		ARGC_MIN_MAX(1, 2);
		string arr_id = ARG_LIT_ID(0);
		int len = arg.size() == 1 ? 0 : ARG_VAR_NUM(1);
		ptm_new_array(arr_id, len);
	};
	CMD("ARR.PUSH") {
		ARGC(2);
		string arr_id = ARG_LIT_ARR_ID(0);
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
		string arr_id = ARG_LIT_ARR_ID(0);
		string var_id = ARG_LIT_ID(1);
		ptm_set_var(var_id, ptm_array_size(arr_id));
	};
	CMD("ARR.SET") {
		ARGC(2);
		string arr_id = ARG_LIT_ARR_ID(0);
		auto& arr = ptm_get_array(arr_id);
		int ix = intp->arg_var_number_for_array_index(arr, arr_id, arg[0]);
		arr[ix] = ARG_VAR_STR(1);
	};
	CMD("ARR.ERASE") {
		ARGC(2);
		string arr_id = ARG_LIT_ARR_ID(0);
		auto& arr = ptm_get_array(arr_id);
		int ix = ARG_VAR_NUM(1);
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
		string arr_id = ARG_LIT_ARR_ID(0);
		intp->arrays[arr_id].clear();
	};
	CMD("ARR.COPY") {
		ARGC(2);
		string src_arr_id = ARG_LIT_ARR_ID(0);
		string dst_arr_id = ARG_LIT_ARR_ID(1);
		ptm_copy_array(dst_arr_id, src_arr_id);
	};
	CMD("ARR.FOR") {
		ARGC(2);
		string arr_id = ARG_LIT_ARR_ID(0);
		string iter_var = ARG_LIT_ID(1);
		intp->array_loop_start(arr_id, iter_var);
	};
	CMD("FOR") {
		ARGC_MIN_MAX(3, 4);
		string id = ARG_LIT_ID(0);
		int first = ARG_VAR_NUM(1);
		int last = ARG_VAR_NUM(2);
		int step = arg.size() == 4 ? ARG_VAR_NUM(3) : 1;
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
		string a = ARG_VAR_STR(0);
		string b = ARG_VAR_STR(1);
		string label = ARG_LIT_LABEL(2);
		if (a == b) {
			intp->goto_label(label);
		}
	};
	CMD("IF.CALL") {
		ARGC(3);
		string a = ARG_VAR_STR(0);
		string b = ARG_VAR_STR(1);
		string label = ARG_LIT_LABEL(2);
		if (a == b) {
			intp->call_label(label);
		}
	};
	CMD("IF.KEY") {
		ARGC(1);
		string keyname = ARG_VAR_STR(0);
		if (!ptm_kb_pressed(keyname)) {
			intp->goto_matching_endif();
		}
	};
	CMD("INKEY") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		ptm_set_var(id, last_key);
		last_key = 0;
	};
	CMD("INC") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		auto& var = ptm_get_var(id);
		ptm_set_var(id, String::ToInt(var.value) + 1);
	};
	CMD("DEC") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		auto& var = ptm_get_var(id);
		ptm_set_var(id, String::ToInt(var.value) - 1);
	};
	CMD("ADD") {
		ARGC(3);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		int b = ARG_VAR_NUM(2);
		ptm_set_var(result, a + b);
	};
	CMD("SUB") {
		ARGC(3);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		int b = ARG_VAR_NUM(2);
		ptm_set_var(result, a - b);
	};
	CMD("MUL") {
		ARGC(3);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		int b = ARG_VAR_NUM(2);
		ptm_set_var(result, a * b);
	};
	CMD("DIV") {
		ARGC(3);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		int b = ARG_VAR_NUM(2);
		ptm_set_var(result, a / b);
	};
	CMD("DIVR") {
		ARGC(3);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		int b = ARG_VAR_NUM(2);
		ptm_set_var(result, a % b);
	};
	CMD("POW") {
		ARGC(3);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		int b = ARG_VAR_NUM(2);
		ptm_set_var(result, pow(a, b));
	};
	CMD("SQRT") {
		ARGC(2);
		string result = ARG_LIT_ID(0);
		int a = ARG_VAR_NUM(1);
		ptm_set_var(result, sqrt(a));
	};
	CMD("FRAMES") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		ptm_set_var(id, scr.frame_counter);
	};
	CMD("CHR") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		binary bin = ARG_VAR_STR(1);
		tileset.set(ix, bin);
	};
	CMD("CHR.LEN") {
		ARGC(1);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, tileset.tiles.size());
	};
	CMD("CHR.GET") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, tileset.get(ix));
	};
	CMD("PAL") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		rgb color = ARG_VAR_NUM(1);
		palette.set(ix, color);
	};
	CMD("PAL.LEN") {
		ARGC(1);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, palette.colors.size());
	};
	CMD("PAL.GET") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, palette.get(ix));
	};
	CMD("PAL.GETR") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, palette.get_r(ix));
	};
	CMD("PAL.GETG") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, palette.get_g(ix));
	};
	CMD("PAL.GETB") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, palette.get_b(ix));
	};
	CMD("PAL.SETR") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		int val = ARG_VAR_NUM(1);
		palette.set_r(ix, val);
	};
	CMD("PAL.SETG") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		int val = ARG_VAR_NUM(1);
		palette.set_g(ix, val);
	};
	CMD("PAL.SETB") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		int val = ARG_VAR_NUM(1);
		palette.set_b(ix, val);
	};
	CMD("BUF.NEW") {
		ARGC(5);
		string id = ARG_LIT_ID(0);
		int layers = ARG_VAR_NUM(1);
		int width = ARG_VAR_NUM(2);
		int height = ARG_VAR_NUM(3);
		int order = ARG_VAR_NUM(4);
		if (tilebufs.has(id)) {
			ptm_abort("Duplicate buffer id: " + id);
		}
		if (tilebufs.get_by_order(order) != nullptr) {
			ptm_abort("Duplicate buffer ordering: " + String::ToString(order));
		}
		else {
			tilebufs.new_tilebuf(id, layers, width, height, order);
		}
	};
	CMD("BUF.VIEW") {
		ARGC(5);
		string id = ARG_LIT_ID(0);
		int x1 = ARG_VAR_NUM(1);
		int y1 = ARG_VAR_NUM(2);
		int x2 = ARG_VAR_NUM(3);
		int y2 = ARG_VAR_NUM(4);
		tilebufs.get(id)->view(x1, y1, x2, y2);
	};
	CMD("BUF.SCRL") {
		ARGC(3);
		string id = ARG_LIT_ID(0);
		int dx = ARG_VAR_NUM(1);
		int dy = ARG_VAR_NUM(2);
		tilebufs.get(id)->scroll_view(dx, dy);
	};
	CMD("BUF.SHOW") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		tilebufs.get(id)->show();
	};
	CMD("BUF.HIDE") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		tilebufs.get(id)->hide();
	};
	CMD("BUF.BCOL") {
		ARGC(2);
		string id = ARG_LIT_ID(0);
		int palette_ix = ARG_VAR_NUM(1);
		tilebufs.get(id)->set_bgcol(palette_ix);
	};
	CMD("BUF.BGOFF") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		tilebufs.get(id)->bg_enabled = false;
	};
	CMD("BUF.SEL") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		tilebufs.select(id);
	};
	CMD("BUF.CLL") {
		ARGC(2);
		string id = ARG_LIT_ID(0);
		int layer = ARG_VAR_NUM(1);
		tilebufs.get(id)->clear_layer(layer);
	};
	CMD("BUF.CLS") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		tilebufs.get(id)->clear_all_layers();
	};
	CMD("CLS") {
		ARGC(0);
		tilebufs.clear_all_buffers();
	};
	CMD("TILE.NEW") {
		ARGC(3);
		int ch = ARG_VAR_NUM(0);
		int fgc = ARG_VAR_NUM(1);
		int bgc = ARG_VAR_NUM(2);
		working_tile.clear();
		working_tile.add(ch, fgc, bgc);
	};
	CMD("TILE.ADD") {
		ARGC(3);
		int ch = ARG_VAR_NUM(0);
		int fgc = ARG_VAR_NUM(1);
		int bgc = ARG_VAR_NUM(2);
		working_tile.add(ch, fgc, bgc);
	};
	CMD("TILE.SETC") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		int ch = ARG_VAR_NUM(1);
		working_tile.set_ch(ix, ch);
	};
	CMD("TILE.SETF") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		int fgc = ARG_VAR_NUM(1);
		working_tile.set_fgc(ix, fgc);
	};
	CMD("TILE.SETB") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		int bgc = ARG_VAR_NUM(1);
		working_tile.set_bgc(ix, bgc);
	};
	CMD("TILE.GETC") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, working_tile.frames[ix].ch);
	};
	CMD("TILE.GETF") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, working_tile.frames[ix].fgc);
	};
	CMD("TILE.GETB") {
		ARGC(2);
		int ix = ARG_VAR_NUM(0);
		string var = ARG_LIT_ID(1);
		ptm_set_var(var, working_tile.frames[ix].bgc);
	};
	CMD("TILE.COLOR") {
		ARGC(3);
		int ix = ARG_VAR_NUM(0);
		int fgc = ARG_VAR_NUM(1);
		int bgc = ARG_VAR_NUM(2);
		working_tile.set_fgc(ix, fgc);
		working_tile.set_bgc(ix, bgc);
	};
	CMD("TILE.LEN") {
		ARGC(1);
		string var = ARG_LIT_ID(0);
		ptm_set_var(var, working_tile.length());
	};
	CMD("TILE.PARSE") {
		ARGC(1);
		string str = ARG_VAR_STR(0);
		bool ok = working_tile.parse(str);
		if (!ok) {
			ptm_abort("Could not parse tile definition: " + str);
		}
	};
	CMD("TILE.STR") {
		ARGC(1);
		string var = ARG_LIT_ID(0);
		ptm_set_var(var, working_tile.to_str());
	};
	CMD("TILE.STORE") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		ptm_store_tile(id, working_tile);
	};
	CMD("TILE.LOAD") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		if (ptm_has_stored_tile(id)) {
			t_tileseq tile = ptm_load_tile(id);
			working_tile.set_equal(tile);
		}
		else {
			ptm_abort("Tile not found in store with id: " + id);
		}
	};
	CMD("TILE.SETP") {
		ARGC(2);
		string prop = ARG_VAR_STR(0);
		string value = ARG_VAR_STR(1);
		working_tile.data.set(prop, value);
	};
	CMD("TILE.GETP") {
		ARGC(2);
		string var = ARG_LIT_ID(0);
		string prop = ARG_VAR_STR(1);
		if (working_tile.data.has(prop)) {
			ptm_set_var(var, working_tile.data.get_s(prop));
		}
		else {
			ptm_set_var(var, "");
		}
	};
	CMD("LAYER") {
		ARGC(1);
		int layer = ARG_VAR_NUM(0);
		if (layer < 0 || layer >= tilebufs.selected()->get_layer_count()) {
			ptm_abort("Invalid layer for selected buffer: " + tilebufs.selected_id());
		}
		tilebuf_csr.layer = layer;
	};
	CMD("LOCATE") {
		ARGC(2);
		int x = ARG_VAR_NUM(0);
		int y = ARG_VAR_NUM(1);
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
	CMD("DELR") {
		ARGC(4);
		int x1 = ARG_VAR_NUM(0);
		int y1 = ARG_VAR_NUM(1);
		int x2 = ARG_VAR_NUM(2);
		int y2 = ARG_VAR_NUM(3);
		ptm_get_selected_tilebuf_layer().clear_rect(x1, y1, x2, y2);
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
	CMD("RECT") {
		ARGC(4);
		int x1 = ARG_VAR_NUM(0);
		int y1 = ARG_VAR_NUM(1);
		int x2 = ARG_VAR_NUM(2);
		int y2 = ARG_VAR_NUM(3);
		ptm_get_selected_tilebuf_layer().fill_rect(working_tile, x1, y1, x2, y2);
	};
	CMD("MOV") {
		ARGC(4);
		int x = ARG_VAR_NUM(0);
		int y = ARG_VAR_NUM(1);
		int dx = ARG_VAR_NUM(2);
		int dy = ARG_VAR_NUM(3);
		ptm_get_selected_tilebuf_layer().move_tile(x, y, dx, dy);
	};
	CMD("MOVB") {
		ARGC(6);
		int x1 = ARG_VAR_NUM(0);
		int y1 = ARG_VAR_NUM(1);
		int x2 = ARG_VAR_NUM(2);
		int y2 = ARG_VAR_NUM(3);
		int dx = ARG_VAR_NUM(4);
		int dy = ARG_VAR_NUM(5);
		ptm_get_selected_tilebuf_layer().move_block(x1, y1, x2, y2, dx, dy);
	};
	CMD("PRINT") {
		ARGC(1);
		string str = ARG_VAR_STR(0);
		ptm_print_tile_string(str, false);
	};
	CMD("PRINT.ADD") {
		ARGC(1);
		string str = ARG_VAR_STR(0);
		ptm_print_tile_string(str, true);
	};
	CMD("PRINTF") {
		ARGC(1);
		string fmt = ARG_VAR_STR(0);
		ptm_print_formatted_tile_string(fmt);
	};
	CMD("PUTC") {
		ARGC(1);
		int ch = ARG_VAR_NUM(0);
		ptm_print_tile_char(ch);
	};
	CMD("FCOL") {
		ARGC(1);
		int fgc = ARG_VAR_NUM(0);
		scr.text_style.fgc = fgc;
	};
	CMD("BCOL") {
		ARGC(1);
		int bgc = ARG_VAR_NUM(0);
		scr.text_style.bgc = bgc;
	};
	CMD("COLOR") {
		ARGC(2);
		int fgc = ARG_VAR_NUM(0);
		int bgc = ARG_VAR_NUM(1);
		scr.text_style.fgc = fgc;
		scr.text_style.bgc = bgc;
	};
	CMD("SND.LOAD") {
		ARGC(2);
		string id = ARG_LIT_ID(0);
		string file = ARG_VAR_STR(1);
		ptm_load_sound_wav(id, file);
	};
	CMD("SND.PLAY") {
		ARGC(1);
		string id = ARG_LIT_ID(0);
		ptm_play_sound_wav(id);
	};
	CMD("SND.STOP") {
		ARGC(0);
		ptm_stop_all_sounds();
	};
	CMD("SPR.NEW") {
		ARGC_MIN_MAX(3, 4);
		string id = ARG_VAR_STR(0);
		int ch = ARG_VAR_NUM(1);
		int fgc = ARG_VAR_NUM(2);
		int bgc = arg.size() == 4 ? ARG_VAR_NUM(3) : 0;
		if (!sprites.has(id)) {
			t_sprite& spr = sprites.new_sprite(id);
			spr.tile = t_tileseq(ch, fgc, bgc);
			if (arg.size() == 3) {
				spr.tile.transparent = true;
			}
		}
		else {
			ptm_abort("Duplicate sprite id: " + id);
		}
	};
	CMD("SPR.X") {
		ARGC(2);
		string id = ARG_VAR_STR(0);
		int x = ARG_VAR_NUM(1);
		t_sprite& spr = sprites.get_sprite(id);
		spr.x = x;
	};
	CMD("SPR.Y") {
		ARGC(2);
		string id = ARG_VAR_STR(0);
		int y = ARG_VAR_NUM(1);
		t_sprite& spr = sprites.get_sprite(id);
		spr.y = y;
	};
	CMD("SPR.POS") {
		ARGC(3);
		string id = ARG_VAR_STR(0);
		int x = ARG_VAR_NUM(1);
		int y = ARG_VAR_NUM(2);
		t_sprite& spr = sprites.get_sprite(id);
		spr.x = x;
		spr.y = y;
	};
	CMD("SPR.MOVE") {
		ARGC(3);
		string id = ARG_VAR_STR(0);
		int dx = ARG_VAR_NUM(1);
		int dy = ARG_VAR_NUM(2);
		t_sprite& spr = sprites.get_sprite(id);
		spr.move(dx, dy);
	};
	CMD("SPR.BUF") {
		ARGC(2);
		string id = ARG_VAR_STR(0);
		string buf_id = ARG_LIT_ID(1);
		t_sprite& spr = sprites.get_sprite(id);
		spr.buf = tilebufs.get(buf_id);
	};
	CMD("SPR.SHOW") {
		ARGC(1);
		string id = ARG_VAR_STR(0);
		t_sprite& spr = sprites.get_sprite(id);
		spr.visible = true;
	};
	CMD("SPR.HIDE") {
		ARGC(1);
		string id = ARG_VAR_STR(0);
		t_sprite& spr = sprites.get_sprite(id);
		spr.visible = false;
	};
	CMD("SPR.DEL") {
		ARGC(1);
		string id = ARG_VAR_STR(0);
		t_sprite& spr = sprites.get_sprite(id);
		sprites.remove(id);
	};
	CMD("READ") {
		ARGC(1);
		string var = ARG_LIT_ID(0);
		if (intp->has_more_data()) {
			ptm_set_var(var, intp->read_data_s());
		}
		else {
			ptm_abort("Out of data");
		}
	};
	CMD("RESTORE") {
		ARGC(0);
		intp->reset_data_pointer();
	};
	CMD("FCHK") {
		ARGC(2);
		string path = ARG_VAR_STR(0);
		string var = ARG_LIT_ID(1);
		bool exists = File::Exists(path);
		ptm_set_var(var, exists ? 1 : 0);
	};
	CMD("CLOAD") {
		ARGC(2);
		string path = ARG_VAR_STR(0);
		string var = ARG_LIT_ID(1);
		string file = ptm_read_text_file(path);
		ptm_set_var(var, file);
	};
	CMD("LLOAD") {
		ARGC(2);
		string path = ARG_VAR_STR(0);
		string arr_id = ARG_LIT_ID(1);
		auto lines = ptm_read_text_file_lines(path);
		ptm_new_array(arr_id, 0);
		auto& arr = ptm_get_array(arr_id);
		for (auto& line : lines) {
			arr.push_back(line);
		}
	};
	CMD("BLOAD") {
		ARGC(2);
		string path = ARG_VAR_STR(0);
		string arr_id = ARG_LIT_ID(1);
		auto data = ptm_read_binary_file(path);
		ptm_new_array(arr_id, 0);
		auto& arr = ptm_get_array(arr_id);
		for (auto& value : data) {
			arr.push_back(String::ToString(value));
		}
	};
	CMD("CSAVE") {
		ARGC(2);
		string path = ARG_VAR_STR(0);
		string text = ARG_VAR_STR(1);
		ptm_write_text_file(path, text);
	};
	CMD("BSAVE") {
		ARGC(2);
		string path = ARG_VAR_STR(0);
		string arr_id = ARG_LIT_ARR_ID(1);
		auto& arr = ptm_get_array(arr_id);
		ptm_write_binary_file(path, arr);
	};
	CMD("RND") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		int min = ARG_VAR_NUM(1);
		int max = ARG_VAR_NUM(2);
		int rnd = ptm_get_random_number(min, max);
		ptm_set_var(var, rnd);
	};
	CMD("STR.CAT") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string str1 = ARG_VAR_STR(1);
		string str2 = ARG_VAR_STR(2);
		ptm_set_var(var, str1 + str2);
	};
	CMD("STR.UCASE") {
		ARGC(2);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		ptm_set_var(var, String::ToUpper(str));
	};
	CMD("STR.LCASE") {
		ARGC(2);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		ptm_set_var(var, String::ToLower(str));
	};
	CMD("STR.SUB") {
		ARGC(4);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		int begin = ARG_VAR_NUM(2);
		int end = ARG_VAR_NUM(3);
		string result = String::Substring(str, begin, end);
		ptm_set_var(var, result);
	};
	CMD("STR.SPLIT") {
		ARGC(3);
		string arr_id = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		string delim = ARG_VAR_STR(2);
		ptm_new_array(arr_id, 0);
		auto& arr = ptm_get_array(arr_id);
		auto split_str = String::Split(str, delim, true);
		for (auto& item : split_str) {
			arr.push_back(item);
		}
	};
	CMD("STR.TRIM") {
		ARGC(2);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		ptm_set_var(var, String::Trim(str));
	};
	CMD("STR.LEN") {
		ARGC(2);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		ptm_set_var(var, str.length());
	};
	CMD("STR.AT") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		int ix = ARG_VAR_NUM(2);
		ptm_set_var(var, str[ix]);
	};
	CMD("STR.FIND") {
		ARGC(4);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		string substr = ARG_VAR_STR(2);
		int offset = ARG_VAR_NUM(3);
		int first = String::FindFirst(str, substr, offset);
		ptm_set_var(var, first);
	};
	CMD("STR.PFX") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		string prefix = ARG_VAR_STR(2);
		ptm_set_var(var, String::StartsWith(str, prefix));
	};
	CMD("STR.SFX") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		string prefix = ARG_VAR_STR(2);
		ptm_set_var(var, String::EndsWith(str, prefix));
	};
	CMD("STR.HAS") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		string substr = ARG_VAR_STR(2);
		ptm_set_var(var, String::Contains(str, substr));
	};
	CMD("STR.REPL") {
		ARGC(4);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		string substr = ARG_VAR_STR(2);
		string replacement = ARG_VAR_STR(3);
		ptm_set_var(var, String::Replace(str, substr, replacement));
	};
	CMD("STR.REPT") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string str = ARG_VAR_STR(1);
		int count = ARG_VAR_NUM(2);
		ptm_set_var(var, String::Repeat(str, count));
	};
	CMD("STR.FMT") {
		ARGC(3);
		string var = ARG_LIT_ID(0);
		string fmt = ARG_VAR_STR(1);
		int number = ARG_VAR_NUM(2);
		ptm_set_var(var, String::Format(fmt.c_str(), number));
	};
	CMD("MML.PLAY") {
		ARGC(1);
		string mml = ARG_VAR_STR(0);
		ptm_mml_play(mml, false);
	};
	CMD("MML.LOOP") {
		ARGC(1);
		string mml = ARG_VAR_STR(0);
		ptm_mml_play(mml, true);
	};
	CMD("MML.STOP") {
		ARGC(0);
		ptm_mml_stop();
	};
	CMD("MML.VOL") {
		ARGC(1);
		int vol = ARG_VAR_NUM(0);
		ptm_mml_volume(vol);
	};
	CMD("BEEP") {
		ARGC(2);
		int freq = ARG_VAR_NUM(0);
		int length = ARG_VAR_NUM(1);
		ptm_mml_beep(freq, length);
	};
	CMD("INPUT") {
		ARGC(2);
		string var = ARG_LIT_ID(0);
		int max_length = ARG_VAR_NUM(1);
		string value = ptm_text_input(max_length);
		ptm_set_var(var, value);
	};
}
