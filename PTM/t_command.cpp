#include "t_command.h"
#include "t_interpreter.h"
#include "t_machine.h"
#include "t_program.h"

#define ARGC(x) if (!intp->argc(arg, x)) return;

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	machine = intp->machine;
}
bool t_command::execute(string& cmd, t_params& args) {
	// Control flow
		 if (cmd == "HALT")			halt(args);
	else if (cmd == "EXIT")			exit(args);
	else if (cmd == "GOTO")			goto_label(args);
	else if (cmd == "CALL")			call_label(args);
	else if (cmd == "RET")			return_from_label(args);
	else if (cmd == "PAUSE")		pause(args);
	// Variables
	else if (cmd == "VAR")			set_variable(args);
	else if (cmd == "RND")			get_random_number(args);
	// Tile buffer cursor
	else if (cmd == "CSR.LAYER")	select_layer(args);
	else if (cmd == "CSR.SET")		set_cursor_pos(args);
	else if (cmd == "CSR.MOV")		move_cursor(args);
	// Current tile
	else if (cmd == "TILE.NEW")		init_cur_tile(args);
	else if (cmd == "TILE.ADD")		append_cur_tile(args);
	else if (cmd == "TILE.CH")		set_cur_tile_char(args);
	else if (cmd == "TILE.FG")		set_cur_tile_fgcolor(args);
	else if (cmd == "TILE.BG")		set_cur_tile_bgcolor(args);
	else if (cmd == "TILE.PARSE")	parse_cur_tile(args);
	else if (cmd == "TILE.STORE")	store_cur_tile(args);
	else if (cmd == "TILE.PSTORE")	parse_and_store_tile(args);
	else if (cmd == "TILE.LOAD")	load_cur_tile(args);
	else if (cmd == "TILE.TRA")		set_tile_transparency(args);
	// Tile buffer
	else if (cmd == "BUF.PUT")		put_tile(args);
	else if (cmd == "BUF.PUT.R")	put_tile_repeat_right(args);
	else if (cmd == "BUF.PUT.L")	put_tile_repeat_left(args);
	else if (cmd == "BUF.PUT.U")	put_tile_repeat_up(args);
	else if (cmd == "BUF.PUT.D")	put_tile_repeat_down(args);
	else if (cmd == "BUF.FILL")		fill_rect(args);
	else if (cmd == "BUF.CLS")		clear_all_layers(args);
	else if (cmd == "BUF.CLL")		clear_layer(args);
	else if (cmd == "BUF.CLR")		clear_rect(args);
	// Window
	else if (cmd == "WND.BG")		set_wnd_bgcolor(args);
	// Graphics
	else if (cmd == "CHR")			define_char(args);
	else if (cmd == "PAL")			define_color(args);
	else if (cmd == "VSYNC")		update_screen(args);
	// Object
	else if (cmd == "OBJ.NEW")		create_obj(args);
	else if (cmd == "OBJ.PROP")		set_obj_prop(args);
	else if (cmd == "OBJ.TILE")		set_obj_tile(args);
	else if (cmd == "OBJ.DRAW")		draw_obj(args);
	// Text output
	else if (cmd == "PRINT")		print_text(args);
	else if (cmd == "TEXT.FG")		set_text_fgcolor(args);
	else if (cmd == "TEXT.BG")		set_text_bgcolor(args);
	else if (cmd == "TEXT.COL")		set_text_colors(args);
	// Keyboard
	else if (cmd == "KEY.GET")		get_key_pressed(args);
	else if (cmd == "KEY.CALL")		call_if_key_pressed(args);
	// Debug
	else if (cmd == "DBG.FILE")		save_debug_file(args);

	else return false;
	return true;
}
std::vector<string> t_command::get_debug_info() {
	std::vector<string> info;
	info.push_back("Variables");
	for (auto& var : machine->vars) {
		info.push_back(String::Format("\t%s = %s", var.first.c_str(), var.second.c_str()));
	}
	info.push_back("");
	info.push_back("Objects");
	for (auto& obj : machine->objs) {
		string id = obj.first;
		t_obj& o = obj.second;
		info.push_back("\tID: " + id);
		info.push_back("\tTiles: " + o.tile.ToString());
		info.push_back("\tProperties: ");
		for (auto& prop : o.prop.Entries) {
			string name = prop.first;
			string value = prop.second;
			info.push_back(String::Format("\t\t%s = %s", name.c_str(), value.c_str()));
		}
	}
	info.push_back("");
	info.push_back("Tilestore");
	for (auto& saved_tile : machine->tilestore) {
		string id = saved_tile.first;
		string tile = saved_tile.second.ToString();
		info.push_back(String::Format("\t%s = %s", id.c_str(), tile.c_str()));
	}
	info.push_back("");
	info.push_back("Current tile");
	info.push_back(String::Format("\t%s", machine->cur_tile.ToString().c_str()));
	info.push_back("");
	info.push_back("Callstack");
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
		if (arg[1].type == t_param_type::id) {
			string src_var = intp->require_existing_varname(arg[1]);
			if (!src_var.empty()) {
				machine->vars[dst_var] = machine->vars[src_var];
			}
		} else if (arg[1].type == t_param_type::obj_prop) {
			t_obj* o = intp->require_obj_prop(arg[1], true);
			if (o) {
				machine->vars[dst_var] = o->prop.GetString(arg[1].prop.name);
			}
		} else {
			machine->vars[dst_var] = arg[1].textual_value;
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
void t_command::init_cur_tile(t_params& arg) {
	ARGC(3);
	TTile tile;
	tile.Char = intp->require_number(arg[0]);
	tile.ForeColor = intp->require_number(arg[1]);
	tile.BackColor = intp->require_number(arg[2]);
	machine->cur_tile.Clear();
	machine->cur_tile.Add(tile);
}
void t_command::append_cur_tile(t_params& arg) {
	ARGC(3);
	TTile tile;
	tile.Char = intp->require_number(arg[0]);
	tile.ForeColor = intp->require_number(arg[1]);
	tile.BackColor = intp->require_number(arg[2]);
	machine->cur_tile.Add(tile);
}
void t_command::set_cur_tile_char(t_params& arg) {
	ARGC(2);
	int frame = intp->require_number(arg[0]);
	if (frame < machine->cur_tile.GetSize()) {
		int ch = intp->require_number(arg[1]);
		machine->cur_tile.SetChar(frame, ch);
	} else {
		intp->abort("Invalid tile frame index");
	}
}
void t_command::set_cur_tile_fgcolor(t_params& arg) {
	ARGC(2);
	int frame = intp->require_number(arg[0]);
	if (frame < machine->cur_tile.GetSize()) {
		int color = intp->require_number(arg[1]);
		machine->cur_tile.SetForeColor(frame, color);
	} else {
		intp->abort("Invalid tile frame index");
	}
}
void t_command::set_cur_tile_bgcolor(t_params& arg) {
	ARGC(2);
	int frame = intp->require_number(arg[0]);
	if (frame < machine->cur_tile.GetSize()) {
		int color = intp->require_number(arg[1]);
		machine->cur_tile.SetBackColor(frame, color);
	} else {
		intp->abort("Invalid tile frame index");
	}
}
void t_command::parse_cur_tile(t_params& arg) {
	ARGC(1);
	string tile = intp->require_string(arg[0]);
	if (!tile.empty()) {
		bool ok = machine->cur_tile.Parse(tile);
		if (!ok) {
			intp->abort("Malformed tile definition");
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
			bool ok = tile.Parse(tile_def);
			if (ok) {
				machine->tilestore[id] = tile;
			} else {
				intp->abort("Malformed tile definition");
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
	machine->tilebuf->SetTile(
		machine->cur_tile, machine->csr.layer, machine->csr.x, machine->csr.y, machine->tile_transparency);
}
void t_command::put_tile_repeat_right(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	for (int i = 0; i < count; i++) {
		const int dest_x = machine->csr.x;
		const int dest_y = machine->csr.y;
		machine->csr.x++;
		machine->tilebuf->SetTile(
			machine->cur_tile, machine->csr.layer, dest_x, dest_y, machine->tile_transparency);
	}
}
void t_command::put_tile_repeat_left(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	for (int i = 0; i < count; i++) {
		const int dest_x = machine->csr.x;
		const int dest_y = machine->csr.y;
		machine->csr.x--;
		machine->tilebuf->SetTile(
			machine->cur_tile, machine->csr.layer, dest_x, dest_y, machine->tile_transparency);
	}
}
void t_command::put_tile_repeat_up(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	for (int i = 0; i < count; i++) {
		const int dest_x = machine->csr.x;
		const int dest_y = machine->csr.y;
		machine->csr.y--;
		machine->tilebuf->SetTile(
			machine->cur_tile, machine->csr.layer, dest_x, dest_y, machine->tile_transparency);
	}
}
void t_command::put_tile_repeat_down(t_params& arg) {
	ARGC(1);
	int count = intp->require_number(arg[0]);
	for (int i = 0; i < count; i++) {
		const int dest_x = machine->csr.x;
		const int dest_y = machine->csr.y;
		machine->csr.y++;
		machine->tilebuf->SetTile(
			machine->cur_tile, machine->csr.layer, dest_x, dest_y, machine->tile_transparency);
	}
}
void t_command::fill_rect(t_params& arg) {
	ARGC(2);
	int w = intp->require_number(arg[0]);
	int h = intp->require_number(arg[1]);
	int dest_x = machine->csr.x;
	int dest_y = machine->csr.y;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			machine->tilebuf->SetTile(
				machine->cur_tile, machine->csr.layer, dest_x + x, dest_y + y, machine->tile_transparency);
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
void t_command::set_wnd_bgcolor(t_params& arg) {
	ARGC(1);
	machine->wnd->SetBackColor(machine->pal->GetColorRGB(intp->require_number(arg[0])));
}
void t_command::set_tile_transparency(t_params& arg) {
	ARGC(1);
	int value = intp->require_number(arg[0]);
	machine->tile_transparency = value > 0;
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
	int chr_ix = intp->require_number(arg[0]);
	int row_ix = intp->require_number(arg[1]);
	int data = intp->require_number(arg[2]);
	machine->chr->Set(chr_ix, row_ix, data);
}
void t_command::define_color(t_params& arg) {
	ARGC(2);
	int pal_ix = intp->require_number(arg[0]);
	int rgb = intp->require_number(arg[1]);
	machine->pal->Set(pal_ix, rgb);
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
	machine->vars[var] = String::ToString(Util::Random(min, max));
}
void t_command::pause(t_params& arg) {
	ARGC(1);
	int cycles = intp->require_number(arg[0]);
	intp->pause_cycles = cycles;
}
void t_command::create_obj(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		if (machine->objs.find(id) == machine->objs.end()) {
			machine->objs[id] = t_obj();
		}
	}
}
void t_command::set_obj_prop(t_params& arg) {
	ARGC(2);
	t_obj* o = intp->require_obj_prop(arg[0], false);
	if (!o) return;
	o->prop.Set(arg[0].prop.name, arg[1].textual_value);
}
void t_command::set_obj_tile(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		auto o = intp->require_existing_obj(arg[0]);
		if (o) {
			o->tile = machine->cur_tile;
		}
	}
}
void t_command::print_text(t_params& arg) {
	ARGC(1);
	string text = intp->require_string(arg[0]);
	if (!text.empty()) {
		const int initial_x = machine->csr.x;
		for (int i = 0; i < text.length(); i++) {
			char ch = text[i];
			if (ch == '\\') {
				i++;
				if (i < text.length()) {
					if (text[i] == 'n') {
						machine->csr.x = initial_x;
						machine->csr.y++;
					}
				}
			} else {
				machine->tilebuf->SetTile(
					TTileSeq(ch, machine->text_color.fg, machine->text_color.bg),
					machine->csr.layer, machine->csr.x, machine->csr.y, machine->tile_transparency);
				machine->csr.x++;
			}
		}
	}
}
void t_command::set_text_fgcolor(t_params& arg) {
	ARGC(1);
	machine->text_color.fg = intp->require_number(arg[0]);
}
void t_command::set_text_bgcolor(t_params& arg) {
	ARGC(1);
	machine->text_color.bg = intp->require_number(arg[0]);
}
void t_command::set_text_colors(t_params& arg) {
	ARGC(2);
	machine->text_color.fg = intp->require_number(arg[0]);
	machine->text_color.bg = intp->require_number(arg[1]);
}
void t_command::draw_obj(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		auto o = intp->require_existing_obj(arg[0]);
		if (o) {
			if (o->prop.Has("layer") && o->prop.Has("x") && o->prop.Has("y")) {
				machine->tilebuf->SetTile(
					o->tile,
					o->prop.GetNumber("layer"),
					o->prop.GetNumber("x"),
					o->prop.GetNumber("y"),
					machine->tile_transparency);
			} else {
				intp->abort("Object is not drawable");
			}
		}
	}
}
void t_command::get_key_pressed(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (!id.empty()) {
		machine->vars[id] = String::ToString(machine->last_key_pressed);
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
void t_command::save_debug_file(t_params& arg) {
	ARGC(1);
	string path = intp->require_string(arg[0]);
	if (!path.empty()) {
		File::WriteLines(path, get_debug_info());
	}
}
