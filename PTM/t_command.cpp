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
	else if (cmd == "GOTO")		branch(args);
	else if (cmd == "VAR")		set_variable(args);
	else if (cmd == "MKV")		create_view(args);
	else if (cmd == "VIEW")		select_view(args);
	else if (cmd == "RVIEW")	unselect_view(args);
	else if (cmd == "LOC")		set_cursor_pos(args);
	else if (cmd == "MVC")		move_cursor(args);
	else if (cmd == "TILE")		append_cur_tile(args);
	else if (cmd == "RTILE")	clear_cur_tile(args);
	else if (cmd == "PUT")		put_tile(args);
	else if (cmd == "FILL")		fill_view(args);
	else if (cmd == "CLS")		clear_all_layers(args);
	else if (cmd == "CLV")		clear_view(args);
	else if (cmd == "BGCOL")	set_wnd_bgcolor(args);
	else if (cmd == "TRANSP")	set_tile_transparency(args);
	else if (cmd == "LAYER")	select_layer(args);
	else if (cmd == "CHR")		define_char(args);

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
void t_command::branch(t_params& arg) {
	ARGC(1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->cur_line_ix = intp->prg->labels[label];
		intp->branched = true;
	}
}
void t_command::set_variable(t_params& arg) {
	ARGC(2);
	string dst_var = intp->require_varname(arg[0]);
	if (!dst_var.empty()) {
		if (arg[1].type == t_param_type::id) {
			string src_var = intp->require_existing_varname(arg[1]);
			if (!src_var.empty()) {
				machine->vars[dst_var] = machine->vars[src_var];
			}
		} else {
			machine->vars[dst_var] = arg[1].textual_value;
		}
	}
}
void t_command::create_view(t_params& arg) {
	ARGC(5);
	string id = intp->require_varname(arg[0]);
	if (!id.empty()) {
		t_view view;
		view.x = intp->require_number(arg[1]);
		view.y = intp->require_number(arg[2]);
		view.w = intp->require_number(arg[3]);
		view.h = intp->require_number(arg[4]);
		machine->views[id] = view;
	}
}
void t_command::select_view(t_params& arg) {
	ARGC(1);
	string id = intp->require_varname(arg[0]);
	if (!id.empty()) {
		if (machine->views.find(id) != machine->views.end()) {
			machine->cur_view = &machine->views[id];
		} else {
			intp->abort("View not found");
		}
	}
}
void t_command::unselect_view(t_params& arg) {
	ARGC(0);
	machine->cur_view = &machine->default_view;
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
void t_command::put_tile(t_params& arg) {
	ARGC(0);
	if (!machine->is_csr_within_view()) return;
	const int dest_x = machine->cur_view->x + machine->csr.x;
	const int dest_y = machine->cur_view->y + machine->csr.y;
	machine->tilebuf->SetTile(
		machine->cur_tile, machine->csr.layer, dest_x, dest_y, machine->tile_transparency);
}
void t_command::fill_view(t_params& arg) {
	ARGC(0);
	int dest_x = machine->cur_view->x + machine->csr.x;
	int dest_y = machine->cur_view->y + machine->csr.y;
	for (int y = 0; y < machine->cur_view->h; y++) {
		for (int x = 0; x < machine->cur_view->w; x++) {
			machine->tilebuf->SetTile(
				machine->cur_tile, machine->csr.layer, dest_x + x, dest_y + y, machine->tile_transparency);
		}
	}
}
void t_command::clear_all_layers(t_params& arg) {
	ARGC(0);
	machine->tilebuf->ClearAllLayers();
}
void t_command::clear_view(t_params& arg) {
	ARGC(0);
	if (!machine->cur_view) return;
	int dest_x = machine->cur_view->x + machine->csr.x;
	int dest_y = machine->cur_view->y + machine->csr.y;
	for (int y = 0; y < machine->cur_view->h; y++) {
		for (int x = 0; x < machine->cur_view->w; x++) {
			machine->tilebuf->EraseTile(machine->csr.layer, dest_x + x, dest_y + y);
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
	ARGC(9);
	int ix = intp->require_number(arg[0]);
	int row1 = intp->require_number(arg[1]);
	int row2 = intp->require_number(arg[2]);
	int row3 = intp->require_number(arg[3]);
	int row4 = intp->require_number(arg[4]);
	int row5 = intp->require_number(arg[5]);
	int row6 = intp->require_number(arg[6]);
	int row7 = intp->require_number(arg[7]);
	int row8 = intp->require_number(arg[8]);
	machine->chr->Set(ix, row1, row2, row3, row4, row5, row6, row7, row8);
}
