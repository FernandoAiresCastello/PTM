#include "t_command.h"
#include "t_interpreter.h"
#include "t_machine.h"
#include "t_program.h"

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	machine = intp->machine;
}
bool t_command::execute(string& cmd, t_params& args) {
	// Control flow
	if (cmd == "HALT")				halt(args);
	else if (cmd == "EXIT")			exit(args);
	else if (cmd == "GOTO")			goto_label(args);
	else if (cmd == "CALL")			call_label(args);
	else if (cmd == "RET")			return_from_label(args);
	else if (cmd == "PAUSE")		pause(args);
	// Variables
	else if (cmd == "VAR")			set_variable(args);
	else if (cmd == "CONST")		define_constant(args);
	// Arrays
	else if (cmd == "ARR.NEW")		create_array(args);
	else if (cmd == "ARR.PUSH")		array_push(args);
	else if (cmd == "ARR.LEN")		get_array_length(args);
	else if (cmd == "ARR.SET")		set_array_element(args);
	else if (cmd == "ARR.ERASE")	erase_array_element(args);
	else if (cmd == "ARR.CLR")		clear_array(args);
	else if (cmd == "ARR.COPY")		copy_array(args);
	// Math
	else if (cmd == "RND")			get_random_number(args);
	else if (cmd == "INC")			increment_variable(args);
	// Current tile
	else if (cmd == "TILE.NEW")		init_cur_tile(args);
	else if (cmd == "TILE.ADD")		append_cur_tile(args);
	else if (cmd == "TILE.CH")		set_cur_tile_char(args);
	else if (cmd == "TILE.FG")		set_cur_tile_fgcolor(args);
	else if (cmd == "TILE.BG")		set_cur_tile_bgcolor(args);
	else if (cmd == "TILE.PARSE")	parse_cur_tile(args);
	else if (cmd == "TILE.STO")		store_cur_tile(args);
	else if (cmd == "TILE.PSTO")	parse_and_store_tile(args);
	else if (cmd == "TILE.LOAD")	load_cur_tile(args);
	// Tile buffer cursor
	else if (cmd == "CSR.LAYER")	select_layer(args);
	else if (cmd == "CSR.SET")		set_cursor_pos(args);
	else if (cmd == "CSR.MOV")		move_cursor(args);
	else if (cmd == "CSR.R")		move_cursor_right(args);
	else if (cmd == "CSR.L")		move_cursor_left(args);
	else if (cmd == "CSR.U")		move_cursor_up(args);
	else if (cmd == "CSR.D")		move_cursor_down(args);
	else if (cmd == "CSR.UR")		move_cursor_up_right(args);
	else if (cmd == "CSR.UL")		move_cursor_up_left(args);
	else if (cmd == "CSR.DR")		move_cursor_down_right(args);
	else if (cmd == "CSR.DL")		move_cursor_down_left(args);
	else if (cmd == "CSR.ON")		set_cursor_visible(args, true);
	else if (cmd == "CSR.OFF")		set_cursor_visible(args, false);
	else if (cmd == "CSR.COLOR")	set_cursor_color(args);
	// Tile buffer
	else if (cmd == "BUF.PUT")		put_tile(args);
	else if (cmd == "BUF.GET")		copy_tile(args);
	else if (cmd == "BUF.DEL")		delete_tile(args);
	else if (cmd == "BUF.REPR")		put_tile_repeat_right(args);
	else if (cmd == "BUF.REPL")		put_tile_repeat_left(args);
	else if (cmd == "BUF.REPU")		put_tile_repeat_up(args);
	else if (cmd == "BUF.REPD")		put_tile_repeat_down(args);
	else if (cmd == "BUF.FILL")		fill_rect(args);
	else if (cmd == "BUF.CLS")		clear_all_layers(args);
	else if (cmd == "BUF.CLL")		clear_layer(args);
	else if (cmd == "BUF.CLR")		clear_rect(args);
	// Graphics / Window
	else if (cmd == "CHR")			define_char(args);
	else if (cmd == "PAL")			define_color(args);
	else if (cmd == "CHR.SIZE")		get_charset_size(args);
	else if (cmd == "PAL.SIZE")		get_palette_size(args);
	else if (cmd == "VSYNC")		update_screen(args);
	else if (cmd == "TITLE")		set_window_title(args);
	else if (cmd == "GFX.BG")		set_window_bgcolor(args);
	else if (cmd == "GFX.TRON")		set_tile_transparency(args, true);
	else if (cmd == "GFX.TROFF")	set_tile_transparency(args, false);
	// Text output
	else if (cmd == "PRINT")		print_text(args, false);
	else if (cmd == "PUTCH")		print_text_char(args);
	else if (cmd == "PRINTL")		print_text(args, true);
	else if (cmd == "TEXT.FG")		set_text_fgcolor(args);
	else if (cmd == "TEXT.BG")		set_text_bgcolor(args);
	else if (cmd == "TEXT.COL")		set_text_colors(args);
	// Keyboard
	else if (cmd == "KEY.GET")		get_key_pressed(args);
	else if (cmd == "KEY.CALL")		call_if_key_pressed(args);
	else if (cmd == "KEY.GOTO")		goto_if_key_pressed(args);
	else if (cmd == "ESCAPE.ON")	allow_exit_on_escape_key(args, true);
	else if (cmd == "ESCAPE.OFF")	allow_exit_on_escape_key(args, false);
	// Debug
	else if (cmd == "BRK")			trigger_breakpoint(args);
	else if (cmd == "DBG.FILE")		save_debug_file(args);
	else if (cmd == "ASSERT.EQ")	assert_eq(args);
	else if (cmd == "ASSERT.NEQ")	assert_neq(args);
	else if (cmd == "ASSERT.GT")	assert_gt(args);
	else if (cmd == "ASSERT.GTE")	assert_gte(args);
	else if (cmd == "ASSERT.LT")	assert_lt(args);
	else if (cmd == "ASSERT.LTE")	assert_lte(args);
	// Conditionals
	else if (cmd == "CMP")			compare_numbers(args);
	else if (cmd == "CMPS")			compare_strings(args);
	else if (cmd == "IF.EQ.CALL")	if_eq_call(args);
	else if (cmd == "IF.NEQ.CALL")	if_neq_call(args);
	else if (cmd == "IF.GT.CALL")	if_gt_call(args);
	else if (cmd == "IF.GTE.CALL")	if_gte_call(args);
	else if (cmd == "IF.LT.CALL")	if_lt_call(args);
	else if (cmd == "IF.LTE.CALL")	if_lte_call(args);
	else if (cmd == "IF.EQ.GOTO")	if_eq_goto(args);
	else if (cmd == "IF.NEQ.GOTO")	if_neq_goto(args);
	else if (cmd == "IF.GT.GOTO")	if_gt_goto(args);
	else if (cmd == "IF.GTE.GOTO")	if_gte_goto(args);
	else if (cmd == "IF.LT.GOTO")	if_lt_goto(args);
	else if (cmd == "IF.LTE.GOTO")	if_lte_goto(args);
	// Sound
	else if (cmd == "SND.PLAY")		play_sound(args);
	else if (cmd == "SND.LOOP")		loop_sound(args);

	else return false;
	return true;
}
std::vector<string> t_command::get_debug_info() {
	std::vector<string> info;
	// Variables
	info.push_back("Variables");
	if (machine->vars.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& var : machine->vars) {
		info.push_back(
			(var.second.is_const ? "\tconst " : "\t") +
			String::Format("%s = %s", var.first.c_str(), var.second.value.c_str()));
	}
	info.push_back("");
	// Arrays
	info.push_back("Arrays");
	if (machine->arrays.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& arr_inst : machine->arrays) {
		string id = arr_inst.first;
		auto& arr = arr_inst.second;
		info.push_back(String::Format("\t%s (length=%i)", id.c_str(), arr.size()));
		for (int i = 0; i < arr.size(); i++) {
			info.push_back(String::Format("\t\t[%i] = %s", i, arr[i].c_str()));
		}
	}
	info.push_back("");
	// Tilestore
	info.push_back("Tilestore");
	if (machine->tilestore.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& saved_tile : machine->tilestore) {
		string id = saved_tile.first;
		string tile = saved_tile.second.ToString();
		info.push_back(String::Format("\t%s = %s", id.c_str(), tile.c_str()));
	}
	info.push_back("");
	// Current tile
	info.push_back("Current tile");
	if (machine->cur_tile.IsEmpty()) {
		info.push_back("\t(empty)");
	} else {
		info.push_back(String::Format("\t%s", machine->cur_tile.ToString().c_str()));
	}
	info.push_back("");
	// Tile buffer cursor
	info.push_back("Tile buffer cursor");
	info.push_back(String::Format("\tLayer=%i X=%i Y=%i", 
		machine->csr.layer, machine->csr.x, machine->csr.y));
	info.push_back("");
	// Callstack
	info.push_back("Callstack");
	if (intp->callstack.empty()) {
		info.push_back("\t(empty)");
	}
	for (auto& prg_ix : intp->callstack._Get_container()) {
		info.push_back("\t" + String::ToString(prg_ix));
	}
	return info;
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
		} if (arg[1].is_array_element_ix()) {
			string value = intp->require_array_element(arg[1]);
			machine->vars[dst_var] = value;
		} else {
			machine->vars[dst_var] = arg[1].textual_value;
		}
	}
}
void t_command::define_constant(t_params& arg) {
	ARGC(2);
	string dst_var = intp->require_id(arg[0]);
	if (!dst_var.empty()) {
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
void t_command::set_cursor_pos(t_params& arg) {
	ARGC(2);
	machine->csr.x = intp->require_number(arg[0]);
	machine->csr.y = intp->require_number(arg[1]);
}
void t_command::move_cursor(t_params& arg) {
	ARGC(2);
	machine->csr.x += intp->require_number(arg[0]);
	machine->csr.y += intp->require_number(arg[1]);
}
void t_command::move_cursor_right(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->csr.x += arg.empty() ? 1 : intp->require_number(arg[0]);
}
void t_command::move_cursor_left(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->csr.x -= arg.empty() ? 1 : intp->require_number(arg[0]);
}
void t_command::move_cursor_up(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->csr.y -= arg.empty() ? 1 : intp->require_number(arg[0]);
}
void t_command::move_cursor_down(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->csr.y += arg.empty() ? 1 : intp->require_number(arg[0]);
}
void t_command::move_cursor_up_right(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->erase_cursor();
	int dist = arg.empty() ? 1 : intp->require_number(arg[0]);
	machine->csr.y -= dist;
	machine->csr.x += dist;
}
void t_command::move_cursor_up_left(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->erase_cursor();
	int dist = arg.empty() ? 1 : intp->require_number(arg[0]);
	machine->csr.y -= dist;
	machine->csr.x -= dist;
}
void t_command::move_cursor_down_right(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->erase_cursor();
	int dist = arg.empty() ? 1 : intp->require_number(arg[0]);
	machine->csr.y += dist;
	machine->csr.x += dist;
}
void t_command::move_cursor_down_left(t_params& arg) {
	ARGC_MIN_MAX(0, 1);
	machine->erase_cursor();
	int dist = arg.empty() ? 1 : intp->require_number(arg[0]);
	machine->csr.y += dist;
	machine->csr.x -= dist;
}
void t_command::set_cursor_visible(t_params& arg, bool visible) {
	ARGC(0);
	machine->csr.visible = visible;
}
void t_command::set_cursor_color(t_params& arg) {
	ARGC(1);
	int color = intp->require_palette_ix(arg[0]);
	if (color != PTM_INVALID_NUMBER) {
		machine->csr.color = color;
	}
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
void t_command::parse_and_store_tile(t_params& arg) {
	ARGC(2);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		string tile_def = intp->require_string(arg[1]);
		if (!tile_def.empty()) {
			TTileSeq tile;
			bool parse_ok = tile.Parse(tile_def);
			if (!parse_ok) {
				intp->abort("Malformed tile definition");
				return;
			}
			if (machine->is_valid_tileseq(tile)) {
				machine->tilestore[id] = tile;
			} else {
				intp->abort("Invalid tile definition");
			}
		}
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
void t_command::put_tile_repeat_right(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			machine->put_cur_tile_at_cursor_pos();
			machine->csr.x++;
			machine->put_cur_tile_at_cursor_pos();
		}
	} else {
		machine->put_cur_tile_at_cursor_pos();
	}
}
void t_command::put_tile_repeat_left(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			machine->put_cur_tile_at_cursor_pos();
			machine->csr.x--;
			machine->put_cur_tile_at_cursor_pos();
		}
	} else {
		machine->put_cur_tile_at_cursor_pos();
	}
}
void t_command::put_tile_repeat_up(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			machine->put_cur_tile_at_cursor_pos();
			machine->csr.y--;
			machine->put_cur_tile_at_cursor_pos();
		}
	} else {
		machine->put_cur_tile_at_cursor_pos();
	}
}
void t_command::put_tile_repeat_down(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			machine->put_cur_tile_at_cursor_pos();
			machine->csr.y++;
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
			machine->tilebuf->SetTile(
				machine->cur_tile, machine->csr.layer, x + px, y + py, machine->tile_transparency);
		}
	}
}
void t_command::clear_all_layers(t_params& arg) {
	ARGC(0);
	machine->tilebuf->ClearAllLayers();
}
void t_command::clear_layer(t_params& arg) {
	ARGC(1);
	int layer = intp->require_number(arg[0]);
	machine->tilebuf->ClearLayer(layer);
}
void t_command::clear_rect(t_params& arg) {
	ARGC(4);
	int x = intp->require_number(arg[0]);
	int y = intp->require_number(arg[1]);
	int w = intp->require_number(arg[2]);
	int h = intp->require_number(arg[3]);
	for (int py = 0; py < h; py++) {
		for (int px = 0; px < w; px++) {
			machine->tilebuf->EraseTile(machine->csr.layer, x + px, y + py);
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
	if (layer >= 0 && layer < machine->tilebuf->LayerCount) {
		machine->csr.layer = layer;
	} else {
		intp->abort("Invalid layer index");
	}
}
void t_command::define_char(t_params& arg) {
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
	int min = intp->require_number(arg[1]);
	int max = intp->require_number(arg[2]);
	machine->set_var(var, Util::Random(min, max));
}
void t_command::pause(t_params& arg) {
	ARGC(1);
	int cycles = intp->require_number(arg[0]);
	intp->pause_cycles = cycles;
}
void t_command::print_text(t_params& arg, bool crlf) {
	ARGC(1);
	string text = intp->require_string(arg[0]);
	if (!text.empty()) {
		if (crlf) {
			text += "\\n";
		}
		const int initial_x = machine->csr.x;
		bool escape = false;
		string escape_seq = "";
		int fgc = machine->text_color.fg;
		int bgc = machine->text_color.bg;
		for (int i = 0; i < text.length(); i++) {
			int ch = text[i];
			if (ch == '\\') {
				i++;
				if (i < text.length()) {
					if (text[i] == 'n') {
						machine->csr.x = initial_x;
						machine->csr.y++;
					}
				}
			} else if (ch == '{') {
				escape = true;
				continue;
			} else if (ch == '}') {
				escape = false;
				if (String::StartsWith(escape_seq, 'c')) {
					string chstr = String::Skip(escape_seq, 1);
					ch = String::ToInt(chstr);
					machine->tilebuf->SetTile(TTileSeq(ch, fgc, bgc),
						machine->csr.layer, machine->csr.x, machine->csr.y, machine->tile_transparency);
					machine->csr.x++;
					escape_seq = "";
					continue;
				} else if (String::StartsWith(escape_seq, 'f')) {
					fgc = String::ToInt(String::Skip(escape_seq, 1));
					escape_seq = "";
					continue;
				} else if (String::StartsWith(escape_seq, "/f")) {
					fgc = machine->text_color.fg;
					escape_seq = "";
					continue;
				} else if (String::StartsWith(escape_seq, 'b')) {
					bgc = String::ToInt(String::Skip(escape_seq, 1));
					escape_seq = "";
					continue;
				} else if (String::StartsWith(escape_seq, "/b")) {
					bgc = machine->text_color.bg;
					escape_seq = "";
					continue;
				} else {
					intp->abort("Invalid escape sequence: " + escape_seq);
				}
			} else if (escape) {
				escape_seq += ch;
				continue;
			} else {
				machine->tilebuf->SetTile(TTileSeq(ch, fgc, bgc), 
					machine->csr.layer, machine->csr.x, machine->csr.y, machine->tile_transparency);
				machine->csr.x++;
				escape_seq = "";
			}
		}
	}
}
void t_command::print_text_char(t_params& arg) {
	ARGC(1);
	int ch = intp->require_number(arg[0]);
	int fgc = machine->text_color.fg;
	int bgc = machine->text_color.bg;
	machine->tilebuf->SetTile(TTileSeq(ch, fgc, bgc),
		machine->csr.layer, machine->csr.x, machine->csr.y, machine->tile_transparency);
	machine->csr.x++;
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
void t_command::get_key_pressed(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		machine->set_var(id, machine->last_key_pressed);
		machine->last_key_pressed = 0;
	}
}
void t_command::call_if_key_pressed(t_params& arg) {
	ARGC(2);
	int key = intp->require_number(arg[0]);
	if (key > 0) {
		string label = intp->require_label(arg[1]);
		if (key == machine->last_key_pressed) {
			machine->last_key_pressed = 0;
			intp->call_label(label);
		}
	}
}
void t_command::goto_if_key_pressed(t_params& arg) {
	ARGC(2);
	int key = intp->require_number(arg[0]);
	if (key > 0) {
		string label = intp->require_label(arg[1]);
		if (key == machine->last_key_pressed) {
			machine->last_key_pressed = 0;
			intp->goto_label(label);
		}
	}
}
void t_command::save_debug_file(t_params& arg) {
	ARGC(0);
	File::WriteLines(PTM_DEBUG_FILE, get_debug_info());
}
void t_command::compare_numbers(t_params& arg) {
	ARGC(2);
	int a = intp->require_number(arg[0]);
	int b = intp->require_number(arg[1]);
	machine->cmp_result = a - b;
}
void t_command::compare_strings(t_params& arg) {
	ARGC(2);
	string a = intp->require_string(arg[0]);
	string b = intp->require_string(arg[1]);
	if (a == b) {
		machine->cmp_result = 0;
	} else {
		machine->cmp_result = -1;
	}
}
void t_command::if_eq_call(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result == 0) {
		intp->call_label(label);
	}
}
void t_command::if_neq_call(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result != 0) {
		intp->call_label(label);
	}
}
void t_command::if_gt_call(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result > 0) {
		intp->call_label(label);
	}
}
void t_command::if_gte_call(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result >= 0) {
		intp->call_label(label);
	}
}
void t_command::if_lt_call(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result < 0) {
		intp->call_label(label);
	}
}
void t_command::if_lte_call(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result <= 0) {
		intp->call_label(label);
	}
}
void t_command::if_eq_goto(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result == 0) {
		intp->goto_label(label);
	}
}
void t_command::if_neq_goto(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result != 0) {
		intp->goto_label(label);
	}
}
void t_command::if_gt_goto(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result > 0) {
		intp->goto_label(label);
	}
}
void t_command::if_gte_goto(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result >= 0) {
		intp->goto_label(label);
	}
}
void t_command::if_lt_goto(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result < 0) {
		intp->goto_label(label);
	}
}
void t_command::if_lte_goto(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty() && machine->cmp_result <= 0) {
		intp->goto_label(label);
	}
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
	string value = intp->require_string(arg[1]);
	machine->arrays[arr_id].push_back(value);
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
void t_command::allow_exit_on_escape_key(t_params& arg, bool allow) {
	ARGC(0);
	machine->exit_key = allow ? SDLK_ESCAPE : 0;
}
void t_command::assert_eq(t_params& arg) {
	ARGC(2);
	string id = intp->require_existing_varname(arg[0]);
	if (id.empty()) return;
	string expected_value = intp->require_string(arg[1]);
	if (machine->vars[id].value != expected_value) {
		intp->abort("Assertion error");
	}
}
void t_command::assert_neq(t_params& arg) {
	ARGC(2);
	string id = intp->require_existing_varname(arg[0]);
	if (id.empty()) return;
	string expected_value = intp->require_string(arg[1]);
	if (machine->vars[id].value == expected_value) {
		intp->abort("Assertion error");
	}
}
void t_command::assert_gt(t_params& arg) {
	ARGC(2);
	string id = intp->require_existing_varname(arg[0]);
	if (id.empty()) return;
	if (not(String::ToInt(machine->vars[id].value) > intp->require_number(arg[1]))) {
		intp->abort("Assertion error");
	}
}
void t_command::assert_gte(t_params& arg) {
	ARGC(2);
	string id = intp->require_existing_varname(arg[0]);
	if (id.empty()) return;
	if (not(String::ToInt(machine->vars[id].value) >= intp->require_number(arg[1]))) {
		intp->abort("Assertion error");
	}
}
void t_command::assert_lt(t_params& arg) {
	ARGC(2);
	string id = intp->require_existing_varname(arg[0]);
	if (id.empty()) return;
	if (not(String::ToInt(machine->vars[id].value) < intp->require_number(arg[1]))) {
		intp->abort("Assertion error");
	}
}
void t_command::assert_lte(t_params& arg) {
	ARGC(2);
	string id = intp->require_existing_varname(arg[0]);
	if (id.empty()) return;
	if (not(String::ToInt(machine->vars[id].value) <= intp->require_number(arg[1]))) {
		intp->abort("Assertion error");
	}
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
