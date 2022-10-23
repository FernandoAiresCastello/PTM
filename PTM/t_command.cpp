#include "t_command.h"
#include "t_interpreter.h"
#include "t_machine.h"
#include "t_program.h"
#include "t_layer.h"

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	machine = intp->machine;
}
bool t_command::execute(string& cmd, t_params& args) {
	// System
	if (cmd == "EXIT") { exit(args); return true; }
	if (cmd == "TITLE") { set_window_title(args); return true; }
	// Execution flow control
	if (cmd == "HALT") { halt(args); return true; }
	if (cmd == "GOTO") { goto_label(args); return true; }
	if (cmd == "CALL") { call_label(args); return true; }
	if (cmd == "RET") { return_from_label(args); return true; }
	if (cmd == "PAUSE") { pause(args); return true; }
	if (cmd == "FOR") { loop_start(args); return true; }
	if (cmd == "NEXT") { loop_end(args); return true; }
	if (cmd == "BRK") { loop_break(args); return true; }
	if (cmd == "CONT") { loop_continue(args); return true; }
	// Conditional blocks
	if (cmd == "IF.EQ") { if_block_start(args, CMP_MODE_EQ); return true; }
	if (cmd == "IF.NEQ") { if_block_start(args, CMP_MODE_NEQ); return true; }
	if (cmd == "IF.GT") { if_block_start(args, CMP_MODE_GT); return true; }
	if (cmd == "IF.GTE") { if_block_start(args, CMP_MODE_GTE); return true; }
	if (cmd == "IF.LT") { if_block_start(args, CMP_MODE_LT); return true; }
	if (cmd == "IF.LTE") { if_block_start(args, CMP_MODE_LTE); return true; }
	if (cmd == "IF.STR.EQ") { if_block_start(args, CMP_MODE_STR_EQ); return true; }
	if (cmd == "IF.STR.NEQ") { if_block_start(args, CMP_MODE_STR_NEQ); return true; }
	if (cmd == "ENDIF") { if_block_end(args); return true; }
	// Variables & Constants
	if (cmd == "VAR") { set_variable(args); return true; }
	if (cmd == "DEF") { define_constant(args); return true; }
	// Arrays
	if (cmd == "ARR.NEW") { create_array(args); return true; }
	if (cmd == "ARR.PUSH") { array_push(args); return true; }
	if (cmd == "ARR.LEN") { get_array_length(args); return true; }
	if (cmd == "ARR.SET") { set_array_element(args); return true; }
	if (cmd == "ARR.ERASE") { erase_array_element(args); return true; }
	if (cmd == "ARR.CLR") { clear_array(args); return true; }
	if (cmd == "ARR.COPY") { copy_array(args); return true; }
	if (cmd == "ARR.FOR") { array_loop_start(args); return true; }
	// Math
	if (cmd == "RND") { get_random_number(args); return true; }
	if (cmd == "INC") { increment_variable(args); return true; }
	if (cmd == "DEC") { decrement_variable(args); return true; }
	if (cmd == "ADD") { math_add(args); return true; }
	if (cmd == "SUB") { math_subtract(args); return true; }
	if (cmd == "MUL") { math_multiply(args); return true; }
	// Current tile manipulation
	if (cmd == "TILE.NEW") { init_cur_tile(args); return true; }
	if (cmd == "TILE.ADD") { append_cur_tile(args); return true; }
	if (cmd == "TILE.CH") { set_cur_tile_char(args); return true; }
	if (cmd == "TILE.INK") { set_cur_tile_fgcolor(args); return true; }
	if (cmd == "TILE.PAPER") { set_cur_tile_bgcolor(args); return true; }
	if (cmd == "TILE.COLOR") { set_cur_tile_colors(args); return true; }
	if (cmd == "TILE.PARSE") { parse_cur_tile(args); return true; }
	if (cmd == "TILE.STORE") { store_cur_tile(args); return true; }
	if (cmd == "TILE.LOAD") { load_cur_tile(args); return true; }
	if (cmd == "TILE.PROP") { set_tile_property(args); return true; }
	if (cmd == "TILE.PGET") { get_tile_property(args); return true; }
	// Cursor
	if (cmd == "LAYER") { select_layer(args); return true; }
	if (cmd == "LOCATE") { set_cursor_pos(args); return true; }
	if (cmd == "CSR.X") { set_cursor_x(args); return true; }
	if (cmd == "CSR.Y") { set_cursor_y(args); return true; }
	if (cmd == "CSR.MOV") { move_cursor(args); return true; }
	if (cmd == "CSR.R") { move_cursor(args, 1, 0); return true; }
	if (cmd == "CSR.L") { move_cursor(args, -1, 0); return true; }
	if (cmd == "CSR.U") { move_cursor(args, 0, -1); return true; }
	if (cmd == "CSR.D") { move_cursor(args, 0, 1); return true; }
	if (cmd == "CSR.UR") { move_cursor(args, 1, -1); return true; }
	if (cmd == "CSR.UL") { move_cursor(args, -1, -1); return true; }
	if (cmd == "CSR.DR") { move_cursor(args, 1, 1); return true; }
	if (cmd == "CSR.DL") { move_cursor(args, -1, 1); return true; }
	// Tile buffer
	if (cmd == "BUF.NEW") { add_tile_buffer(args); return true; }
	if (cmd == "BUF.SEL") { select_tile_buffer(args); return true; }
	if (cmd == "BUF.SHOW") { show_tile_buffer(args, true); return true; }
	if (cmd == "BUF.HIDE") { show_tile_buffer(args, false); return true; }
	if (cmd == "BUF.VIEW") { set_viewport(args); return true; }
	if (cmd == "BUF.SCRL") { scroll_viewport(args); return true; }
	if (cmd == "BUF.W") { get_buffer_width(args); return true; }
	if (cmd == "BUF.H") { get_buffer_height(args); return true; }
	// Tile output
	if (cmd == "PUT") { put_tile(args); return true; }
	if (cmd == "GET") { copy_tile(args); return true; }
	if (cmd == "DEL") { delete_tile(args); return true; }
	if (cmd == "PUT.R") { put_tile_move_repeat(args, 1, 0); return true; }
	if (cmd == "PUT.L") { put_tile_move_repeat(args, -1, 0); return true; }
	if (cmd == "PUT.U") { put_tile_move_repeat(args, 0, -1); return true; }
	if (cmd == "PUT.D") { put_tile_move_repeat(args, 0, 1); return true; }
	if (cmd == "PUT.UR") { put_tile_move_repeat(args, 1, -1); return true; }
	if (cmd == "PUT.UL") { put_tile_move_repeat(args, -1, -1); return true; }
	if (cmd == "PUT.DR") { put_tile_move_repeat(args, 1, 1); return true; }
	if (cmd == "PUT.DL") { put_tile_move_repeat(args, -1, 1); return true; }
	if (cmd == "RECT") { fill_rect(args); return true; }
	if (cmd == "FILL") { fill_layer(args); return true; }
	if (cmd == "CLS") { clear_all_layers(args); return true; }
	if (cmd == "CLL") { clear_layer(args); return true; }
	if (cmd == "CLR") { clear_rect(args); return true; }
	if (cmd == "MOV") { move_tile(args); return true; }
	if (cmd == "MOVB") { move_tile_block(args); return true; }
	if (cmd == "DRAW") { draw_tile_sequence(args); return true; }
	// Text output
	if (cmd == "PRINT") { print_text(args, false, false); return true; }
	if (cmd == "PRINT.ADD") { print_text(args, false, true); return true; }
	if (cmd == "PRINTL") { print_text(args, true, false); return true; }
	if (cmd == "PUTC") { print_text_char(args); return true; }
	if (cmd == "INK") { set_text_fgcolor(args); return true; }
	if (cmd == "PAPER") { set_text_bgcolor(args); return true; }
	if (cmd == "COLOR") { set_text_colors(args); return true; }
	// Screen
	if (cmd == "VSYNC") { update_screen(args); return true; }
	if (cmd == "BGCOL") { set_window_bgcolor(args); return true; }
	if (cmd == "TRON") { set_tile_transparency(args, true); return true; }
	if (cmd == "TROFF") { set_tile_transparency(args, false); return true; }
	// Character set management
	if (cmd == "CHR") { define_char_byte(args); return true; }
	if (cmd == "CHRB") { define_char(args); return true; }
	if (cmd == "CHR.LEN") { get_charset_size(args); return true; }
	if (cmd == "CHR.GETB") { get_charset_binary_string(args); return true; }
	if (cmd == "CHR.SETB") { set_charset_binary_string(args); return true; }
	// Color palette management
	if (cmd == "PAL") { define_color(args); return true; }
	if (cmd == "PAL.LEN") { get_palette_size(args); return true; }
	if (cmd == "PAL.CLR") { clear_palette(args); return true; }
	if (cmd == "PAL.GET") { get_palette_color(args); return true; }
	if (cmd == "PAL.GETR") { get_palette_color_comp(args, COLOR_R); return true; }
	if (cmd == "PAL.GETG") { get_palette_color_comp(args, COLOR_G); return true; }
	if (cmd == "PAL.GETB") { get_palette_color_comp(args, COLOR_B); return true; }
	if (cmd == "PAL.SETR") { set_palette_color_comp(args, COLOR_R); return true; }
	if (cmd == "PAL.SETG") { set_palette_color_comp(args, COLOR_G); return true; }
	if (cmd == "PAL.SETB") { set_palette_color_comp(args, COLOR_B); return true; }
	// User input
	if (cmd == "INPUT") { read_user_input_string(args); return true; }
	if (cmd == "INKEY") { get_keycode_pressed(args); return true; }
	if (cmd == "XON") { allow_exit_on_escape_key(args, true); return true; }
	if (cmd == "XOFF") { allow_exit_on_escape_key(args, false); return true; }
	// Debugging
	if (cmd == "DBG.BRK") { trigger_breakpoint(args); return true; }
	if (cmd == "DBG.DUMP") { save_debug_file(args); return true; }
	if (cmd == "DBG.PERFMON") { enable_perfmon(args); return true; }
	if (cmd == "DBG.MSG") { show_msgbox(args); return true; }
	// Sound
	if (cmd == "PLAY") { play_sound(args); return true; }
	if (cmd == "LPLAY") { loop_sound(args); return true; }
	if (cmd == "SOUND") { play_sound_note(args); return true; }
	if (cmd == "VOL") { set_sound_volume(args); return true; }
	if (cmd == "QUIET") { stop_sound(args); return true; }
	// Filesystem
	if (cmd == "CLOAD") { read_file_into_string(args); return true; }
	if (cmd == "BLOAD") { read_file_into_byte_array(args); return true; }
	if (cmd == "CSAVE") { write_string_to_file(args); return true; }
	if (cmd == "BSAVE") { write_byte_array_to_file(args); return true; }
	// String manipulation
	if (cmd == "STR.FMT") { format_number(args); return true; }
	if (cmd == "STR.SUBST") { get_substring(args); return true; }
	if (cmd == "STR.LEN") { get_string_length(args); return true; }
	if (cmd == "STR.REPT") { repeat_string(args); return true; }
	if (cmd == "STR.CAT") { concatenate_strings(args); return true; }
	if (cmd == "STR.SPLIT") { split_string(args); return true; }
	if (cmd == "STR.TRIM") { trim_string(args); return true; }
	if (cmd == "STR.UCASE") { uppercase_string(args); return true; }
	if (cmd == "STR.LCASE") { lowercase_string(args); return true; }
	if (cmd == "STR.REPL") { replace_string(args); return true; }
	if (cmd == "STR.AT") { get_string_char_at(args); return true; }
	if (cmd == "STR.IX") { get_string_index_of(args); return true; }
	// Timing
	if (cmd == "TIME") { get_cycles(args); return true; }

	return false;
}
void t_command::nop(t_params& arg) {
	ARGC(0);
}
void t_command::halt(t_params& arg) {
	ARGC(0);
	intp->halted = true;
}
void t_command::exit(t_params& arg) {
	ARGC(0);
	intp->running = false;
}
void t_command::goto_label(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->goto_label(label);
	}
}
void t_command::call_label(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->call_label(label);
	}
}
void t_command::return_from_label(t_params& arg) {
	ARGC(0);
	intp->return_from_call();
}
void t_command::set_variable(t_params& arg) {
	ARGC(2);
	string dst_var = intp->require_id(arg[0]);
	if (!dst_var.empty()) {
		if (machine->vars.find(dst_var) != machine->vars.end() && machine->vars[dst_var].is_const) {
			intp->abort("Constant cannot be modified: " + dst_var);
			return;
		}
		if (arg[1].type == t_param_type::id) {
			string src_var = intp->require_existing_varname(arg[1]);
			if (!src_var.empty()) {
				machine->vars[dst_var] = machine->vars[src_var];
				machine->vars[dst_var].is_const = false;
			}
		} else if (arg[1].is_array_element_ix()) {
			string value = intp->require_array_element(arg[1]);
			machine->vars[dst_var] = value;
		} else if (arg[1].type == t_param_type::char_literal) {
			machine->vars[dst_var] = arg[1].numeric_value;
		} else {
			machine->vars[dst_var] = arg[1].textual_value;
		}
	}
}
void t_command::define_constant(t_params& arg) {
	ARGC(2);
	string dst_var = intp->require_id(arg[0]);
	if (!dst_var.empty()) {
		if (machine->vars.find(dst_var) != machine->vars.end()) {
			intp->abort("Duplicated constant: " + dst_var);
			return;
		}
		if (arg[1].type == t_param_type::id) {
			string src_var = intp->require_existing_varname(arg[1]);
			if (!src_var.empty()) {
				machine->vars[dst_var] = machine->vars[src_var];
				machine->vars[dst_var].is_const = true;
			}
		} else {
			machine->vars[dst_var] = arg[1].textual_value;
			machine->vars[dst_var].is_const = true;
		}
	}
}
void t_command::set_cursor_x(t_params& arg) {
	ARGC(1);
	int x = intp->require_number(arg[0]);
	machine->set_cursor_pos(x, machine->get_csr_y());
}
void t_command::set_cursor_y(t_params& arg) {
	ARGC(1);
	int y = intp->require_number(arg[0]);
	machine->set_cursor_pos(machine->get_csr_x(), y);
}
void t_command::set_cursor_pos(t_params& arg) {
	ARGC(2);
	int x = intp->require_number(arg[0]);
	int y = intp->require_number(arg[1]);
	machine->set_cursor_pos(x, y);
}
void t_command::move_cursor(t_params& arg, int dx, int dy) {
	ARGC_MIN_MAX(0, 1);
	int dist = arg.empty() ? 1 : intp->require_number(arg[0]);
	for (int i = 0; i < dist; i++) {
		machine->move_cursor(dx, dy);
	}
}
void t_command::move_cursor(t_params& arg) {
	ARGC(2);
	int dist_x = intp->require_number(arg[0]);
	int dist_y = intp->require_number(arg[1]);
	machine->move_cursor(dist_x, dist_y);
}
void t_command::init_cur_tile(t_params& arg) {
	ARGC_MIN_MAX(0, 3);
	if (arg.empty()) {
		machine->cur_tile.Clear();
	} else if (arg.size() == 3) {
		TTile tile;
		tile.Char = intp->require_charset_ix(arg[0]);
		tile.ForeColor = intp->require_palette_ix(arg[1]);
		tile.BackColor = intp->require_palette_ix(arg[2]);
		machine->cur_tile.Clear();
		machine->cur_tile.Add(tile);
	} else {
		intp->abort("Invalid argument count");
	}
}
void t_command::append_cur_tile(t_params& arg) {
	ARGC(3);
	TTile tile;
	tile.Char = intp->require_charset_ix(arg[0]);
	tile.ForeColor = intp->require_palette_ix(arg[1]);
	tile.BackColor = intp->require_palette_ix(arg[2]);
	machine->cur_tile.Add(tile);
}
void t_command::set_cur_tile_char(t_params& arg) {
	ARGC(2);
	int frame = intp->require_tile_frame_ix(machine->cur_tile, arg[0]);
	if (frame != PTM_INVALID_NUMBER) {
		int ch = intp->require_charset_ix(arg[1]);
		if (ch != PTM_INVALID_NUMBER) {
			machine->cur_tile.SetChar(frame, ch);
		}
	}
}
void t_command::set_cur_tile_fgcolor(t_params& arg) {
	ARGC(2);
	int frame = intp->require_tile_frame_ix(machine->cur_tile, arg[0]);
	if (frame != PTM_INVALID_NUMBER) {
		int color = intp->require_palette_ix(arg[1]);
		if (color != PTM_INVALID_NUMBER) {
			machine->cur_tile.SetForeColor(frame, color);
		}
	}
}
void t_command::set_cur_tile_bgcolor(t_params& arg) {
	ARGC(2);
	int frame = intp->require_tile_frame_ix(machine->cur_tile, arg[0]);
	if (frame != PTM_INVALID_NUMBER) {
		int color = intp->require_palette_ix(arg[1]);
		if (color != PTM_INVALID_NUMBER) {
			machine->cur_tile.SetBackColor(frame, color);
		}
	}
}
void t_command::set_cur_tile_colors(t_params& arg) {
	ARGC(3);
	int frame = intp->require_tile_frame_ix(machine->cur_tile, arg[0]);
	if (frame != PTM_INVALID_NUMBER) {
		int fgc = intp->require_palette_ix(arg[1]);
		int bgc = intp->require_palette_ix(arg[2]);
		if (fgc != PTM_INVALID_NUMBER && bgc != PTM_INVALID_NUMBER) {
			machine->cur_tile.SetForeColor(frame, fgc);
			machine->cur_tile.SetBackColor(frame, bgc);
		}
	}
}
void t_command::parse_cur_tile(t_params& arg) {
	ARGC(1);
	string tile = intp->require_string(arg[0]);
	if (!tile.empty()) {
		bool parse_ok = machine->cur_tile.Parse(tile);
		if (!parse_ok) {
			intp->abort("Malformed tile definition");
		} else if (!machine->is_valid_tileseq(machine->cur_tile)) {
			intp->abort("Invalid tile definition");
		}
	}
}
void t_command::store_cur_tile(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		machine->tilestore[id] = machine->cur_tile;
	}
}
void t_command::load_cur_tile(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (machine->tilestore.find(id) != machine->tilestore.end()) {
		machine->cur_tile = machine->tilestore[id];
	} else {
		intp->abort("Tile definition not found: " + id);
	}
}
void t_command::set_tile_property(t_params& arg) {
	ARGC(2);
	string prop_id = intp->require_string(arg[0]);
	if (prop_id.empty()) return;
	string prop_value = intp->require_string(arg[1]);
	machine->cur_tile.Prop.Set(prop_id, prop_value);
}
void t_command::get_tile_property(t_params& arg) {
	ARGC(2);
	string var_id = intp->require_id(arg[0]);
	if (var_id.empty()) return;
	string prop_id = intp->require_string(arg[1]);
	if (prop_id.empty()) return;
	if (machine->cur_tile.Prop.Has(prop_id)) {
		machine->set_var(var_id, machine->cur_tile.Prop.GetString(prop_id));
	} else {
		machine->set_var(var_id, "");
	}
}
void t_command::put_tile(t_params& arg) {
	ARGC(0);
	machine->put_cur_tile_at_cursor_pos();
}
void t_command::copy_tile(t_params& arg) {
	ARGC(0);
	machine->copy_tile_at_cursor_pos();
}
void t_command::delete_tile(t_params& arg) {
	ARGC(0);
	machine->delete_tile_at_cursor_pos();
}
void t_command::put_tile_move_repeat(t_params& arg, int dx, int dy) {
	ARGC_MIN_MAX(0, 1);
	int count = arg.empty() ? 1 : intp->require_number(arg[0]);
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			machine->put_cur_tile_at_cursor_pos();
			machine->move_cursor(dx, dy);
			machine->put_cur_tile_at_cursor_pos();
		}
	} else {
		machine->put_cur_tile_at_cursor_pos();
	}
}
void t_command::fill_rect(t_params& arg) {
	ARGC(4);
	int x = intp->require_number(arg[0]);
	int y = intp->require_number(arg[1]);
	int w = intp->require_number(arg[2]);
	int h = intp->require_number(arg[3]);
	for (int py = 0; py < h; py++) {
		for (int px = 0; px < w; px++) {
			machine->cur_buf->SetTile(
				machine->cur_tile, machine->get_csr_layer(), 
				x + px, y + py, machine->tile_transparency);
		}
	}
}
void t_command::fill_layer(t_params& arg) {
	ARGC(0);
	machine->cur_buf->FillLayer(machine->get_csr_layer(), machine->cur_tile, machine->tile_transparency);
}
void t_command::clear_all_layers(t_params& arg) {
	ARGC(0);
	machine->cur_buf->ClearAllLayers();
}
void t_command::clear_layer(t_params& arg) {
	ARGC(0);
	machine->cur_buf->ClearLayer(machine->get_csr_layer());
}
void t_command::clear_rect(t_params& arg) {
	ARGC(4);
	int x = intp->require_number(arg[0]);
	int y = intp->require_number(arg[1]);
	int w = intp->require_number(arg[2]);
	int h = intp->require_number(arg[3]);
	for (int py = 0; py < h; py++) {
		for (int px = 0; px < w; px++) {
			machine->cur_buf->EraseTile(machine->get_csr_layer(), x + px, y + py);
		}
	}
}
void t_command::set_window_bgcolor(t_params& arg) {
	ARGC(1);
	int color = intp->require_palette_ix(arg[0]);
	if (color != PTM_INVALID_NUMBER) {
		machine->set_window_bgcolor(color);
	}
}
void t_command::set_tile_transparency(t_params& arg, bool transparent) {
	ARGC(0);
	machine->tile_transparency = transparent;
}
void t_command::select_layer(t_params& arg) {
	ARGC(1);
	int layer = intp->require_number(arg[0]);
	if (layer == t_layer::bottom || layer == t_layer::top || layer == t_layer::overlay) {
		machine->set_csr_layer(layer);
	} else {
		intp->abort("Invalid layer index");
	}
}
void t_command::select_layer(t_params& arg, int layer) {
	ARGC(0);
	machine->set_csr_layer(layer);
}
void t_command::define_char(t_params& arg) {
	ARGC(9);
	int chr_ix = intp->require_charset_ix(arg[0]);
	if (chr_ix != PTM_INVALID_NUMBER) {
		int row0 = intp->require_number(arg[1]);
		int row1 = intp->require_number(arg[2]);
		int row2 = intp->require_number(arg[3]);
		int row3 = intp->require_number(arg[4]);
		int row4 = intp->require_number(arg[5]);
		int row5 = intp->require_number(arg[6]);
		int row6 = intp->require_number(arg[7]);
		int row7 = intp->require_number(arg[8]);
		machine->chr->Set(chr_ix, row0, row1, row2, row3, row4, row5, row6, row7);
	}
}
void t_command::define_char_byte(t_params& arg) {
	ARGC(3);
	int chr_ix = intp->require_charset_ix(arg[0]);
	if (chr_ix != PTM_INVALID_NUMBER) {
		int row_ix = intp->require_number(arg[1]);
		int data = intp->require_number(arg[2]);
		if (machine->is_valid_char_def(row_ix, data)) {
			machine->chr->Set(chr_ix, row_ix, data);
		} else {
			intp->abort("Invalid char definition");
		}
	}
}
void t_command::define_color(t_params& arg) {
	ARGC(2);
	int pal_ix = intp->require_palette_ix(arg[0]);
	if (pal_ix != PTM_INVALID_NUMBER) {
		int rgb = intp->require_number(arg[1]);
		if (machine->is_valid_color_rgb(rgb)) {
			machine->pal->Set(pal_ix, rgb);
		} else {
			intp->abort("Invalid color RGB definition");
		}
	}
}
void t_command::update_screen(t_params& arg) {
	ARGC(0);
	machine->wnd->Update();
}
void t_command::get_random_number(t_params& arg) {
	ARGC(3);
	string var = intp->require_id(arg[0]);
	if (var.empty()) return;
	int min = intp->require_number(arg[1]);
	if (min == PTM_INVALID_NUMBER) return;
	int max = intp->require_number(arg[2]);
	if (max == PTM_INVALID_NUMBER) return;
	machine->set_var(var, Util::Random(min, max));
}
void t_command::pause(t_params& arg) {
	ARGC(1);
	int cycles = intp->require_number(arg[0]);
	if (cycles == PTM_INVALID_NUMBER) return;
	intp->pause_cycles = cycles;
}
void t_command::print_text(t_params& arg, bool crlf, bool add_frames) {
	ARGC(1);
	string text = intp->require_string(arg[0]);
	machine->print_text(text, crlf, add_frames);
}
void t_command::print_text_char(t_params& arg) {
	ARGC(1);
	int ch = intp->require_number(arg[0]);
	int fgc = machine->text_color.fg;
	int bgc = machine->text_color.bg;
	auto tile = TTileSeq(ch, fgc, bgc);
	machine->put_tile_at_cursor_pos(tile);
}
void t_command::set_text_fgcolor(t_params& arg) {
	ARGC(1);
	int color = intp->require_palette_ix(arg[0]);
	if (color != PTM_INVALID_NUMBER) {
		machine->text_color.fg = color;
	}
}
void t_command::set_text_bgcolor(t_params& arg) {
	int color = intp->require_palette_ix(arg[0]);
	if (color != PTM_INVALID_NUMBER) {
		machine->text_color.bg = color;
	}
}
void t_command::set_text_colors(t_params& arg) {
	ARGC(2);
	int fg = intp->require_palette_ix(arg[0]);
	if (fg != PTM_INVALID_NUMBER) {
		machine->text_color.fg = fg;
	}
	int bg = intp->require_palette_ix(arg[1]);
	if (bg != PTM_INVALID_NUMBER) {
		machine->text_color.bg = bg;
	}
}
void t_command::get_keycode_pressed(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	machine->set_var(id, machine->last_keycode_pressed);
	machine->last_keycode_pressed = 0;
}
void t_command::save_debug_file(t_params& arg) {
	ARGC(0);
	machine->save_debug_file();
}
void t_command::show_msgbox(t_params& arg) {
	ARGC(1);
	string msg = intp->require_string(arg[0]);
	MsgBox::Info("PTM", msg);
}
void t_command::play_sound(t_params& arg) {
	ARGC(1);
	string notes = intp->require_string(arg[0]);
	machine->snd->PlaySubSound(notes);
}
void t_command::loop_sound(t_params& arg) {
	ARGC(1);
	string notes = intp->require_string(arg[0]);
	machine->snd->PlayMainSound(notes);
}
void t_command::set_sound_volume(t_params& arg) {
	ARGC(1);
	int volume = intp->require_number(arg[0]);
	if (volume == PTM_INVALID_NUMBER) return;
	machine->snd->SetVolume(volume * 100);
}
void t_command::stop_sound(t_params& arg) {
	ARGC(0);
	machine->snd->StopMainSound();
	machine->snd->StopSubSound();
}
void t_command::create_array(t_params& arg) {
	ARGC_MIN_MAX(1, 2);
	string arr_id = intp->require_id(arg[0]);
	if (arr_id.empty()) return;
	int len = arg.size() == 1 ? 0 : intp->require_number(arg[1]);
	if (len >= 0) {
		machine->arrays[arr_id] = std::vector<string>();
		for (int i = 0; i < len; i++) {
			machine->arrays[arr_id].push_back("");
		}
	} else {
		intp->abort("Illegal array length");
	}
}
void t_command::array_push(t_params& arg) {
	ARGC(2);
	string arr_id = intp->require_existing_array(arg[0]);
	if (arr_id.empty()) return;
	if (arg[1].type == t_param_type::char_literal) {
		string value = String::ToString(arg[1].numeric_value);
		machine->arrays[arr_id].push_back(value);
	} else {
		string value = arg[1].textual_value;
		machine->arrays[arr_id].push_back(value);
	}
}
void t_command::get_array_length(t_params& arg) {
	ARGC(2);
	string arr_id = intp->require_existing_array(arg[0]);
	if (arr_id.empty()) return;
	string var_id = intp->require_id(arg[1]);
	if (var_id.empty()) return;
	machine->set_var(var_id, machine->arrays[arr_id].size());
}
void t_command::set_array_element(t_params& arg) {
	ARGC(2);
	string arr_id = intp->require_existing_array(arg[0]);
	if (arr_id.empty()) return;
	auto& arr = machine->arrays[arr_id];
	int ix = intp->require_array_index(arr, arg[0]);
	if (ix != PTM_INVALID_NUMBER) {
		arr[ix] = intp->require_string(arg[1]);
	}
}
void t_command::erase_array_element(t_params& arg) {
	ARGC(1);
	string arr_id = intp->require_existing_array(arg[0]);
	if (arr_id.empty()) return;
	auto& arr = machine->arrays[arr_id];
	int ix = intp->require_array_index(arr, arg[0]);
	if (ix != PTM_INVALID_NUMBER) {
		if (!arr.empty()) {
			arr.erase(arr.begin() + ix);
		} else {
			intp->abort("Array is empty: " + arr_id);
		}
	}
}
void t_command::clear_array(t_params& arg) {
	ARGC(1);
	string arr_id = intp->require_existing_array(arg[0]);
	if (arr_id.empty()) return;
	machine->arrays[arr_id].clear();
}
void t_command::copy_array(t_params& arg) {
	ARGC(2);
	string src_arr_id = intp->require_existing_array(arg[0]);
	if (src_arr_id.empty()) return;
	string dest_arr_id = intp->require_existing_array(arg[1]);
	if (dest_arr_id.empty()) return;
	machine->arrays[dest_arr_id] = machine->arrays[src_arr_id];
}
void t_command::increment_variable(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	auto& var = machine->vars[id];
	machine->set_var(id, String::ToInt(var.value) + 1);
}
void t_command::decrement_variable(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	auto& var = machine->vars[id];
	machine->set_var(id, String::ToInt(var.value) - 1);
}
void t_command::math_add(t_params& arg) {
	ARGC(3);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int a = intp->require_number(arg[1]);
	if (a == PTM_INVALID_NUMBER) return;
	int b = intp->require_number(arg[2]);
	if (b == PTM_INVALID_NUMBER) return;
	auto& var = machine->vars[id];
	machine->set_var(id, a + b);
}
void t_command::math_subtract(t_params& arg) {
	ARGC(3);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int a = intp->require_number(arg[1]);
	if (a == PTM_INVALID_NUMBER) return;
	int b = intp->require_number(arg[2]);
	if (b == PTM_INVALID_NUMBER) return;
	auto& var = machine->vars[id];
	machine->set_var(id, a - b);
}
void t_command::math_multiply(t_params& arg) {
	ARGC(3);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int a = intp->require_number(arg[1]);
	if (a == PTM_INVALID_NUMBER) return;
	int b = intp->require_number(arg[2]);
	if (b == PTM_INVALID_NUMBER) return;
	auto& var = machine->vars[id];
	machine->set_var(id, a * b);
}
void t_command::allow_exit_on_escape_key(t_params& arg, bool allow) {
	ARGC(0);
	machine->exit_key = allow ? SDLK_ESCAPE : 0;
}
void t_command::set_window_title(t_params& arg) {
	ARGC(1);
	machine->wnd->SetTitle(intp->require_string(arg[0]));
}
void t_command::get_charset_size(t_params& arg) {
	ARGC(1);
	string var = intp->require_id(arg[0]);
	machine->set_var(var, machine->chr->GetSize());
}
void t_command::get_palette_size(t_params& arg) {
	ARGC(1);
	string var = intp->require_id(arg[0]);
	machine->set_var(var, machine->pal->GetSize());
}
void t_command::trigger_breakpoint(t_params& arg) {
	debugger;
}
void t_command::play_sound_note(t_params& arg) {
	ARGC(2);
	int freq = intp->require_number(arg[0]);
	if (freq < 0) {
		intp->abort(String::Format("Invalid note frequency: %i", freq));
		return;
	}
	int len = intp->require_number(arg[1]);
	if (len < 0) {
		intp->abort(String::Format("Invalid note length: %i", len));
		return;
	}
	machine->snd->Beep(freq, len);
}
void t_command::read_file_into_string(t_params& arg) {
	ARGC(2);
	string path = String::Trim(intp->require_string(arg[0]));
	if (path.empty()) {
		intp->abort("Pathname is empty");
		return;
	}
	if (!File::Exists(path)) {
		intp->abort("File not found: " + path);
		return;
	}
	string var = intp->require_id(arg[1]);
	string file = File::ReadText(path);
	machine->set_var(var, file);
}
void t_command::read_file_into_byte_array(t_params& arg) {
	ARGC(2);
	string path = String::Trim(intp->require_string(arg[0]));
	if (path.empty()) {
		intp->abort("Pathname is empty");
		return;
	}
	if (!File::Exists(path)) {
		intp->abort("File not found: " + path);
		return;
	}
	auto file = File::ReadBytes(path);
	string arr_id = intp->require_id(arg[1]);
	auto& arr = machine->arrays[arr_id];
	for (auto byte : file) {
		arr.push_back(String::ToString(byte));
	}
}
void t_command::write_string_to_file(t_params& arg) {
	ARGC(2);
	string path = String::Trim(intp->require_string(arg[0]));
	if (path.empty()) {
		intp->abort("Pathname is empty");
		return;
	}
	string str = intp->require_string(arg[1]);
	File::WriteText(path, str);
}
void t_command::write_byte_array_to_file(t_params& arg) {
	ARGC(2);
	string path = String::Trim(intp->require_string(arg[0]));
	if (path.empty()) {
		intp->abort("Pathname is empty");
		return;
	}
	File file(path, File::Mode::WriteBinary);
	string arr_id = intp->require_existing_array(arg[1]);
	if (arr_id.empty()) return;
	auto& arr = machine->arrays[arr_id];
	for (auto value : arr) {
		file.WriteByte((byte)String::ToInt(value));
	}
}
void t_command::format_number(t_params& arg) {
	ARGC(3);
	string dest_id = intp->require_id(arg[0]);
	if (dest_id.empty()) return;
	string fmt = intp->require_string(arg[1]);
	int number = intp->require_number(arg[2]);
	if (number == PTM_INVALID_NUMBER) return;
	machine->vars[dest_id] = String::Format(fmt.c_str(), number);
}
void t_command::get_cycles(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	machine->set_var(id, machine->clock);
}
void t_command::read_user_input_string(t_params& arg) {
	ARGC(2);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int maxlen = intp->require_number(arg[1]);
	if (maxlen == PTM_INVALID_NUMBER) return;
	string value = machine->read_input_string(maxlen);
	machine->set_var(id, value);
}
void t_command::move_tile(t_params& arg) {
	ARGC(2);
	int dx = intp->require_number(arg[0]);
	int dy = intp->require_number(arg[1]);
	if (dx == PTM_INVALID_NUMBER || dy == PTM_INVALID_NUMBER) return;
	machine->move_tile_at_cursor_pos(dx, dy);
}
void t_command::move_tile_block(t_params& arg) {
	ARGC(6);
	int x = intp->require_number(arg[0]);
	int y = intp->require_number(arg[1]);
	int w = intp->require_number(arg[2]);
	int h = intp->require_number(arg[3]);
	int dx = intp->require_number(arg[4]);
	int dy = intp->require_number(arg[5]);
	
	if (x == PTM_INVALID_NUMBER || y == PTM_INVALID_NUMBER ||
		w == PTM_INVALID_NUMBER || h == PTM_INVALID_NUMBER ||
		dx == PTM_INVALID_NUMBER || dy == PTM_INVALID_NUMBER) return;

	machine->move_tile_block(x, y, w, h, dx, dy);
}
void t_command::set_viewport(t_params& arg) {
	ARGC(4);
	int x = intp->require_number(arg[0]);
	int y = intp->require_number(arg[1]);
	int cols = intp->require_number(arg[2]);
	int rows = intp->require_number(arg[3]);

	if (x == PTM_INVALID_NUMBER || y == PTM_INVALID_NUMBER ||
		cols == PTM_INVALID_NUMBER || rows == PTM_INVALID_NUMBER) return;

	machine->cur_buf->SetView(x, y, cols, rows);
}
void t_command::scroll_viewport(t_params& arg) {
	ARGC(2);
	int dx = intp->require_number(arg[0]);
	int dy = intp->require_number(arg[1]);
	
	if (dx == PTM_INVALID_NUMBER || dy == PTM_INVALID_NUMBER || dx < 0 || dy < 0) return;

	machine->cur_buf->View.ScrollX += dx;
	machine->cur_buf->View.ScrollY += dy;
}
void t_command::add_tile_buffer(t_params& arg) {
	ARGC(4);
	string id = intp->require_id(arg[0]);
	int cols = intp->require_number(arg[1]);
	int rows = intp->require_number(arg[2]);
	int layers = intp->require_number(arg[3]);

	if (id.empty() || cols == PTM_INVALID_NUMBER || rows == PTM_INVALID_NUMBER || 
		layers == PTM_INVALID_NUMBER) return;

	machine->tilebufs[id] = machine->wnd->AddBuffer(layers, cols, rows);
}
void t_command::show_tile_buffer(t_params& arg, bool visible) {
	ARGC(0);
	machine->cur_buf->View.Visible = visible;
}
void t_command::select_tile_buffer(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	if (machine->tilebufs.find(id) == machine->tilebufs.end()) {
		intp->abort("Tile buffer not found: " + id);
		return;
	}
	machine->cur_buf = machine->tilebufs[id];
}
void t_command::get_buffer_width(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	machine->set_var(id, machine->cur_buf->Cols);
}
void t_command::get_buffer_height(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	machine->set_var(id, machine->cur_buf->Rows);
}
void t_command::enable_perfmon(t_params& arg) {
	ARGC(0);
	machine->show_perfmon = true;
}
void t_command::loop_start(t_params& arg) {
	ARGC_MIN_MAX(3,4);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int first = intp->require_number(arg[1]);
	if (first == PTM_INVALID_NUMBER) return;
	int last = intp->require_number(arg[2]);
	if (last == PTM_INVALID_NUMBER) return;
	int step = arg.size() == 4 ? intp->require_number(arg[3]) : 1;
	if (step == PTM_INVALID_NUMBER) return;
	intp->loop_start(id, first, last, step);
}
void t_command::array_loop_start(t_params& arg) {
	ARGC(2);
	string arr_id = intp->require_existing_array(arg[0]);
	if (arr_id.empty()) return;
	string iter_var = intp->require_id(arg[1]);
	if (iter_var.empty()) return;
	intp->array_loop_start(arr_id, iter_var);
}
void t_command::loop_end(t_params& arg) {
	ARGC(0);
	intp->loop_end();
}
void t_command::loop_break(t_params& arg) {
	ARGC(0);
	intp->loop_break();
}
void t_command::loop_continue(t_params& arg) {
	ARGC(0);
	intp->loop_continue();
}
void t_command::if_block_start(t_params& arg, int cmp_mode) {
	ARGC(2);
	if (cmp_mode == CMP_MODE_STR_EQ || cmp_mode == CMP_MODE_STR_NEQ) {
		string a = intp->require_string(arg[0]);
		string b = intp->require_string(arg[1]);
		if (cmp_mode == CMP_MODE_STR_EQ) {
			if (a == b) { return; } else { intp->goto_matching_endif(); }
		} else {
			if (a != b) { return; } else { intp->goto_matching_endif(); }
		}
	} else {
		int a = intp->require_number(arg[0]);
		if (a == PTM_INVALID_NUMBER) return;
		int b = intp->require_number(arg[1]);
		if (b == PTM_INVALID_NUMBER) return;

		if (cmp_mode == CMP_MODE_EQ) {
			if (a == b) { return; } else { intp->goto_matching_endif(); }
		} else if (cmp_mode == CMP_MODE_NEQ) {
			if (a != b) { return; } else { intp->goto_matching_endif(); }
		} else if (cmp_mode == CMP_MODE_GT) {
			if (a > b) { return; } else { intp->goto_matching_endif(); }
		} else if (cmp_mode == CMP_MODE_GTE) {
			if (a >= b) { return; } else { intp->goto_matching_endif(); }
		} else if (cmp_mode == CMP_MODE_LT) {
			if (a < b) { return; } else { intp->goto_matching_endif(); }
		} else if (cmp_mode == CMP_MODE_LTE) {
			if (a <= b) { return; } else { intp->goto_matching_endif(); }
		}
	}
}
void t_command::if_block_end(t_params& arg) {
	ARGC(0);
}
void t_command::clear_palette(t_params& arg) {
	ARGC(0);
	machine->pal->Clear();
}
void t_command::get_palette_color(t_params& arg) {
	ARGC(2);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int pal_ix = intp->require_palette_ix(arg[1]);
	if (pal_ix == PTM_INVALID_NUMBER) return;
	machine->set_var(id, machine->pal->GetColorRGB(pal_ix));
}
void t_command::get_palette_color_comp(t_params& arg, int comp) {
	ARGC(2);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int pal_ix = intp->require_palette_ix(arg[1]);
	if (pal_ix == PTM_INVALID_NUMBER) return;
	int value = PTM_INVALID_NUMBER;
	if (comp == COLOR_R) value = machine->pal->Get(pal_ix).R;
	else if (comp == COLOR_G) value = machine->pal->Get(pal_ix).G;
	else if (comp == COLOR_B) value = machine->pal->Get(pal_ix).B;
	machine->set_var(id, value);
}
void t_command::set_palette_color_comp(t_params& arg, int comp) {
	ARGC(2);
	int pal_ix = intp->require_palette_ix(arg[0]);
	if (pal_ix == PTM_INVALID_NUMBER) return;
	int value = intp->require_number(arg[1]);
	if (value == PTM_INVALID_NUMBER) return;
	
	if (value < 0) value = 0;
	else if (value > 255) value = 255;
	
	if (comp == COLOR_R) machine->pal->Get(pal_ix).R = value;
	else if (comp == COLOR_G) machine->pal->Get(pal_ix).G = value;
	else if (comp == COLOR_B) machine->pal->Get(pal_ix).B = value;
}
void t_command::get_charset_binary_string(t_params& arg) {
	ARGC(2);
	string id = intp->require_id(arg[0]);
	if (id.empty()) return;
	int chr_ix = intp->require_charset_ix(arg[1]);
	if (chr_ix == PTM_INVALID_NUMBER) return;
	machine->set_var(id, machine->chr->Get(chr_ix).ToBinaryString());
}
void t_command::set_charset_binary_string(t_params& arg) {
	ARGC(2);
	int chr_ix = intp->require_charset_ix(arg[0]);
	if (chr_ix == PTM_INVALID_NUMBER) return;
	string bin = intp->require_string(arg[1]);
	if (bin.empty()) return;
	machine->chr->Set(chr_ix, bin);
}
void t_command::get_substring(t_params& arg) {
	ARGC(4);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string src = intp->require_string(arg[1]);
	int begin = intp->require_number(arg[2]);
	if (begin == PTM_INVALID_NUMBER) return;
	int end = intp->require_number(arg[3]);
	if (begin == PTM_INVALID_NUMBER) return;
	machine->set_var(dest, String::Substring(src, begin, end));
}
void t_command::get_string_length(t_params& arg) {
	ARGC(2);
	string var = intp->require_id(arg[0]);
	if (var.empty()) return;
	string str = intp->require_string(arg[1]);
	machine->set_var(var, str.size());
}
void t_command::repeat_string(t_params& arg) {
	ARGC(3);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	int count = intp->require_number(arg[1]);
	if (count == PTM_INVALID_NUMBER) return;
	string src = intp->require_string(arg[2]);
	string str = "";
	for (int i = 0; i < count; i++) {
		str += src;
	}
	machine->set_var(dest, str);
}
void t_command::concatenate_strings(t_params& arg) {
	ARGC(3);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string src1 = intp->require_string(arg[1]);
	string src2 = intp->require_string(arg[2]);
	machine->set_var(dest, src1 + src2);
}
void t_command::split_string(t_params& arg) {
	ARGC(3);
	string arr_id = intp->require_id(arg[0]);
	if (arr_id.empty()) return;
	string src = intp->require_string(arg[1]);
	int separator = PTM_INVALID_NUMBER;
	if (arg[2].type == t_param_type::string) {
		separator = arg[2].textual_value[0];
	} else {
		separator = intp->require_number(arg[2]);
	}
	if (separator == PTM_INVALID_NUMBER) return;
	machine->arrays[arr_id] = String::Split(src, separator, false);
}
void t_command::trim_string(t_params& arg) {
	ARGC(2);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string src = intp->require_string(arg[1]);
	machine->set_var(dest, String::Trim(src));
}
void t_command::uppercase_string(t_params& arg) {
	ARGC(2);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string src = intp->require_string(arg[1]);
	machine->set_var(dest, String::ToUpper(src));
}
void t_command::lowercase_string(t_params& arg) {
	ARGC(2);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string src = intp->require_string(arg[1]);
	machine->set_var(dest, String::ToLower(src));
}
void t_command::replace_string(t_params& arg) {
	ARGC(4);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string src = intp->require_string(arg[1]);
	string old_str = intp->require_string(arg[2]);
	string new_str = intp->require_string(arg[3]);
	machine->set_var(dest, String::Replace(src, old_str, new_str));
}
void t_command::get_string_char_at(t_params& arg) {
	ARGC(3);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string str = intp->require_string(arg[1]);
	int index = intp->require_number(arg[2]);
	if (index == PTM_INVALID_NUMBER) return;
	machine->set_var(dest, str.at(index));
}
void t_command::get_string_index_of(t_params& arg) {
	ARGC(3);
	string dest = intp->require_id(arg[0]);
	if (dest.empty()) return;
	string str = intp->require_string(arg[1]);
	int ch = intp->require_number(arg[2]);
	if (ch == PTM_INVALID_NUMBER) return;
	int ix = String::IndexOf(str, ch);
	machine->set_var(dest, ix);
}
void t_command::draw_tile_sequence(t_params& arg) {
	ARGC(1);
	string seq = intp->require_string(arg[0]);
	if (seq.empty()) return;
	machine->draw_tile_sequence(seq);
}
