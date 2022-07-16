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
	if		(cmd == "HALT")		halt(args);
	else if (cmd == "EXIT")		exit(args);
	else if (cmd == "GOTO")		goto_label(args);
	else if (cmd == "CALL")		call_label(args);
	else if (cmd == "RET")		return_from_label(args);
	else if (cmd == "VAR")		set_variable(args);
	else if (cmd == "CSR")		set_cursor_pos(args);
	else if (cmd == "CSRM")		move_cursor(args);
	else if (cmd == "TILE")		init_cur_tile(args);
	else if (cmd == "TILE+")	append_cur_tile(args);
	else if (cmd == "STILE")	store_cur_tile(args);
	else if (cmd == "LTILE")	load_cur_tile(args);
	else if (cmd == "PUT")		put_tile(args);
	else if (cmd == "PUTR")		put_tile_repeat_right(args);
	else if (cmd == "PUTL")		put_tile_repeat_left(args);
	else if (cmd == "PUTU")		put_tile_repeat_up(args);
	else if (cmd == "PUTD")		put_tile_repeat_down(args);
	else if (cmd == "FILL")		fill_rect(args);
	else if (cmd == "CLS")		clear_all_layers(args);
	else if (cmd == "CLL")		clear_layer(args);
	else if (cmd == "CLR")		clear_rect(args);
	else if (cmd == "BGCOL")	set_wnd_bgcolor(args);
	else if (cmd == "TRANSP")	set_tile_transparency(args);
	else if (cmd == "LAYER")	select_layer(args);
	else if (cmd == "CHR")		define_char(args);
	else if (cmd == "PAL")		define_color(args);
	else if (cmd == "REFR")		update_screen(args);
	else if (cmd == "RND")		get_random_number(args);
	else if (cmd == "MOV")		move_tile(args);
	else if (cmd == "PAUSE")	pause(args);
	else if (cmd == "OBJ")		create_obj(args);
	else if (cmd == "SET")		set_obj_prop(args);
	else if (cmd == "OBJT")		set_obj_tile(args);

	else return false;
	return true;
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
		intp->cur_line_ix = intp->prg->labels[label];
		intp->branched = true;
	}
}
void t_command::call_label(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->callstack.push(intp->cur_line_ix + 1);
		intp->cur_line_ix = intp->prg->labels[label];
		intp->branched = true;
	}
}
void t_command::return_from_label(t_params& arg) {
	ARGC(0);
	if (!intp->callstack.empty()) {
		intp->cur_line_ix = intp->callstack.top();
		intp->callstack.pop();
		intp->branched = true;
	} else {
		intp->abort("Call stack is empty");
	}
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
void t_command::clear_cur_tile(t_params& arg) {
	ARGC(0);
	machine->cur_tile.Clear();
}
void t_command::store_cur_tile(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	machine->saved_tiles[id] = machine->cur_tile;
	machine->cur_tile.Clear();
}
void t_command::load_cur_tile(t_params& arg) {
	ARGC(1);
	string id = intp->require_id(arg[0]);
	if (machine->saved_tiles.find(id) != machine->saved_tiles.end()) {
		machine->cur_tile = machine->saved_tiles[id];
	} else {
		machine->cur_tile.Clear();
	}
}
void t_command::put_tile(t_params& arg) {
	ARGC(0);
	const int dest_x = machine->csr.x;
	const int dest_y = machine->csr.y;
	machine->tilebuf->SetTile(
		machine->cur_tile, machine->csr.layer, dest_x, dest_y, machine->tile_transparency);
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
void t_command::move_tile(t_params& arg) {
	ARGC(4);
	int src_x = intp->require_number(arg[0]);
	int src_y = intp->require_number(arg[1]);
	int dist_x = intp->require_number(arg[2]);
	int dist_y = intp->require_number(arg[3]);
	auto& src = machine->tilebuf->GetTile(machine->csr.layer, src_x, src_y);
	machine->tilebuf->SetTile(src, machine->csr.layer, src_x + dist_x, src_y + dist_y, machine->tile_transparency);
	machine->tilebuf->EraseTile(machine->csr.layer, src_x, src_y);
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
		machine->cur_obj = &machine->objs[id];
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
		if (machine->objs.find(id) != machine->objs.end()) {
			machine->objs[id].tile = machine->cur_tile;
			machine->cur_tile.Clear();
		} else {
			intp->abort("Object not found: " + id);
		}
	}
}
