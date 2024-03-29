#include "ptm_core.h"
#include "ptm_commands.h"
#include "ptm_graphics_base.h"
#include "ptm_keyboard.h"
#include "ptm_mml.h"
#include "ptm_color_palette.h"
#include "ptm_tile_system.h"
#include "ptm_sprites.h"
#include "ptm_sound_system.h"
#include "../PTML/t_program.h"
#include "../PTML/t_compiler.h"
#include "../PTML/t_interpreter.h"

string main_program_file;
t_program* prg = nullptr;
t_interpreter* intp = nullptr;
t_compiler* compiler = nullptr;
bool reset_requested = false;
const char xor_encryption_key = '#';

void ptm_abort_from_compiler();
void ptm_abort_from_interpreter();

int ptm_run(string program_file)
{
	do {
		SDL_Init(SDL_INIT_EVERYTHING);
		ptm_init_commands();
		ptm_init_mml();

		prg = new t_program();
		if (!prg->load_plain(program_file)) {
			delete prg;     prg = nullptr;
			return 1;
		}
		main_program_file = program_file;

		compiler = new t_compiler();
		compiler->run(prg);
		if (!compiler->errors.empty()) {
			ptm_abort_from_compiler();
		}
		if (compiler->has_window_def) {
			auto& wnd = compiler->window_def;
			ptm_init_window(wnd.width, wnd.height, wnd.size, 0x000000, wnd.default_buf_layer_count);
		}
		else {
			ptm_init_window(360, 200, 3, 0x000000, 1);
		}
		delete compiler;    compiler = nullptr;

		intp = new t_interpreter();
		intp->on_exec_line = ptm_on_exec_line;
		intp->on_idle_loop = ptm_idle_frame;
		intp->on_abort = ptm_abort_from_interpreter;
		intp->run(prg);

		ptm_delete_interpreter();
	}
	while (reset_requested);

	return 0;
}
void ptm_save_encrypted_program(t_program* prg, string dest_file)
{
	vector<string> encrypted_lines;
	for (auto& line : prg->src_lines) {
		encrypted_lines.push_back(Util::XorEncrypt(line.text, xor_encryption_key));
	}
	string encrypted = String::Join(encrypted_lines);
	File::WriteText(dest_file, encrypted);
}
void ptm_abort(string msg)
{
	intp->abort(msg);
}
void ptm_exit()
{
	ptm_free_window();
	ptm_destroy_mml();
	ptm_stop_all_sounds();
	ptm_delete_interpreter();
	SDL_Quit();
	exit(0);
}
void ptm_delete_interpreter()
{
	delete intp;    intp = nullptr;
	delete prg;     prg = nullptr;
}
void ptm_reset()
{
	reset_requested = true;

	intp->stop();
	palette.reset();
	ptm_reset_tilesystem();
	sprites.remove_all();
	ptm_free_window();
	ptm_destroy_mml();
	ptm_stop_all_sounds();
	SDL_Quit();
}
void ptm_halt()
{
	while (true) {
		ptm_update();
	}
}
void ptm_abort_from_compiler()
{
	MsgBox::Error(PTM_MSGBOX_TITLE, compiler->errors[0]);
	ptm_exit();
}
void ptm_abort_from_interpreter()
{
	MsgBox::Error(PTM_MSGBOX_TITLE, intp->errors[0]);
	ptm_exit();
}
void ptm_update()
{
	ptm_refresh_window();
	ptm_proc_events();
}
void ptm_proc_events()
{
	SDL_Event e = { 0 };
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			ptm_exit();
			return;
		}
		else if (e.type == SDL_KEYDOWN) {
			const SDL_Keycode key = e.key.keysym.sym;
			last_key = key;
			if (key == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
				ptm_toggle_fullscreen();
				return;
			}
		}
	}
}
void ptm_idle_frame()
{
	ptm_update();
}
void ptm_show_message_box(string msg)
{
	MsgBox::Info(PTM_MSGBOX_TITLE, msg);
}
void ptm_on_exec_line(t_program_line* line, string& cmd, t_params& params)
{
	try {
		ptm_commands[cmd](params);
	}
	catch (bad_function_call ex) {
		intp->abort("Command not found");
	}
}
bool ptm_has_var(string name)
{
	return intp->vars.find(name) != intp->vars.end();
}
void ptm_set_var(string name, string value)
{
	intp->vars[name].value = value;
	intp->vars[name].is_const = false;
}
void ptm_set_var(string name, int value)
{
	intp->vars[name].value = String::ToString(value);
	intp->vars[name].is_const = false;
}
t_variable& ptm_get_var(string name)
{
	if (!ptm_has_var(name)) {
		intp->abort("Variable not found: " + name);
	}
	return intp->vars[name];
}
void ptm_copy_var(string dst, string src)
{
	intp->vars[dst] = intp->vars[src];
	intp->vars[dst].is_const = false;
}
void ptm_copy_var_to_const(string dst, string src)
{
	intp->vars[dst] = intp->vars[src];
	intp->vars[dst].is_const = true;
}
void ptm_def_const(string name, string value)
{
	if (ptm_has_var(name)) {
		intp->abort("Constant already defined: " + name);
	}
	else {
		intp->vars[name] = t_variable(value, true);
	}
}
void ptm_def_const(string name, int value)
{
	if (ptm_has_var(name)) {
		intp->abort("Constant already defined: " + name);
	}
	else {
		intp->vars[name] = t_variable(value, true);
	}
}
void ptm_new_array(string name, int size)
{
	if (size >= 0) {
		intp->arrays[name] = std::vector<string>();
		for (int i = 0; i < size; i++) {
			intp->arrays[name].push_back("");
		}
	}
	else {
		intp->abort("Illegal array length");
	}
}
void ptm_array_push(string name, string value)
{
	intp->arrays[name].push_back(value);
}
void ptm_array_push(string name, int value)
{
	intp->arrays[name].push_back(String::ToString(value));
}
int ptm_array_size(string name)
{
	return intp->arrays[name].size();
}
vector<string>& ptm_get_array(string name)
{
	return intp->arrays[name];
}
void ptm_copy_array(string dst, string src)
{
	intp->arrays[dst] = intp->arrays[src];
}
void ptm_if_block_start(t_params& arg, int cmp_mode)
{
	if (cmp_mode == CMP_MODE_EQ || cmp_mode == CMP_MODE_NEQ) {
		if (arg[1].type == t_param_type::char_literal) {
			int a = intp->arg_var_number(arg[0]);
			int b = intp->arg_var_number(arg[1]);

			if (cmp_mode == CMP_MODE_EQ) {
				if (a == b) { return; } // execute block
				else { intp->goto_matching_endif(); } // skip block
			}
			else if (cmp_mode == CMP_MODE_NEQ) {
				if (a != b) { return; } // execute block
				else { intp->goto_matching_endif(); } // skip block
			}
		}
		else {
			string a = intp->arg_var_string(arg[0]);
			string b = intp->arg_var_string(arg[1]);

			if (cmp_mode == CMP_MODE_EQ) {
				if (a == b) { return; } // execute block
				else { intp->goto_matching_endif(); } // skip block
			}
			else if (cmp_mode == CMP_MODE_NEQ) {
				if (a != b) { return; } // execute block
				else { intp->goto_matching_endif(); } // skip block
			}
		}
	}
	else if (cmp_mode == CMP_MODE_TRUE || cmp_mode == CMP_MODE_FALSE) {
		int value = intp->arg_var_number(arg[0]);
		if (value == PTM_INVALID_NUMBER) return;

		if (cmp_mode == CMP_MODE_TRUE) {
			if (value > 0) { return; } // execute block
			else { intp->goto_matching_endif(); } // skip block
		}
		else if (cmp_mode == CMP_MODE_FALSE) {
			if (value <= 0) { return; } // execute block
			else { intp->goto_matching_endif(); } // skip block
		}
	}
	else {
		int a = intp->arg_var_number(arg[0]);
		if (a == PTM_INVALID_NUMBER) return;
		int b = intp->arg_var_number(arg[1]);
		if (b == PTM_INVALID_NUMBER) return;

		if (cmp_mode == CMP_MODE_GT) {
			if (a > b) { return; } // execute block
			else { intp->goto_matching_endif(); } // skip block
		}
		else if (cmp_mode == CMP_MODE_GTE) {
			if (a >= b) { return; } // execute block
			else { intp->goto_matching_endif(); } // skip block
		}
		else if (cmp_mode == CMP_MODE_LT) {
			if (a < b) { return; } // execute block
			else { intp->goto_matching_endif(); } // skip block
		}
		else if (cmp_mode == CMP_MODE_LTE) {
			if (a <= b) { return; } // execute block
			else { intp->goto_matching_endif(); } // skip block
		}
	}
}
int ptm_get_random_number(int min, int max)
{
	return Util::Random(min, max);
}
string ptm_sprintf(string fmt)
{
	string result;
	bool escape = false;
	string escape_seq = "";

	for (int i = 0; i < fmt.length(); i++) {
		int ch = fmt[i];
		if (ch == '\\') {
			i++;
			if (i < fmt.length()) {
				if (fmt[i] == 'n') {
					result += "\n";
				}
			}
		}
		else if (ch == '{') {
			escape = true;
			continue;
		}
		else if (ch == '}') {
			escape = false;
			const string upper_escape_seq = String::ToUpper(escape_seq);
			if (String::StartsWith(upper_escape_seq, 'C')) {
				if (escape_seq[1] == '%') {
					string var = String::Skip(escape_seq, 2);
					if (String::Contains(var, '[') || String::Contains(var, ']')) {
						auto begin = String::IndexOf(var, '[');
						auto end = String::IndexOf(var, ']');
						if (begin != string::npos && end != string::npos && begin < end) {
							string arr_id = String::Substring(var, 0, begin - 1);
							if (intp->arrays.find(arr_id) != intp->arrays.end()) {
								string ixs = String::Substring(var, begin + 1, end - 1);
								int ix = -1;
								if (String::IsNumber(ixs)) {
									ix = String::ToInt(ixs);
								}
								else {
									if (intp->vars.find(ixs) != intp->vars.end()) {
										ix = String::ToInt(intp->vars[ixs].value);
									}
									else {
										intp->abort("Variable not found: " + ixs);
									}
								}
								if (ix >= 0 && ix < intp->arrays[arr_id].size()) {
									ch = String::ToInt(intp->arrays[arr_id].at(ix));
								}
								else {
									intp->abort(String::Format("Array index out of bounds: %s[%i]", arr_id.c_str(), ix));
								}
							}
							else {
								intp->abort("Array not found: " + arr_id);
							}
						}
					}
					else {
						if (intp->vars.find(var) != intp->vars.end()) {
							ch = String::ToInt(intp->vars[var].value);
						}
						else {
							intp->abort("Variable not found: " + var);
						}
					}
				}
				else {
					ch = String::ToInt(String::Skip(String::Replace(upper_escape_seq, "&H", "0x"), 1));
					result += char(ch);
				}
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, 'F')) {
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, "/F")) {
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, 'B')) {
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(upper_escape_seq, "/B")) {
				escape_seq = "";
				continue;
			}
			else if (String::StartsWith(escape_seq, '%')) {
				string var = String::Skip(escape_seq, 1);
				if (String::Contains(var, '[') || String::Contains(var, ']')) {
					auto begin = String::IndexOf(var, '[');
					auto end = String::IndexOf(var, ']');
					if (begin != string::npos && end != string::npos && begin < end) {
						string arr_id = String::Substring(var, 0, begin - 1);
						if (intp->arrays.find(arr_id) != intp->arrays.end()) {
							string ixs = String::Substring(var, begin + 1, end - 1);
							int ix = -1;
							if (String::IsNumber(ixs)) {
								ix = String::ToInt(ixs);
							}
							else {
								if (intp->vars.find(ixs) != intp->vars.end()) {
									ix = String::ToInt(intp->vars[ixs].value);
								}
								else {
									intp->abort("Variable not found: " + ixs);
								}
							}
							if (ix >= 0 && ix < intp->arrays[arr_id].size()) {
								string str = intp->arrays[arr_id].at(ix);
								result += str;
							}
							else {
								intp->abort(String::Format("Array index out of bounds: %s[%i]", arr_id.c_str(), ix));
							}
						}
						else {
							intp->abort("Array not found: " + arr_id);
						}
					}
				}
				else {
					if (intp->vars.find(var) != intp->vars.end()) {
						result += intp->vars[var].value;
					}
					else {
						intp->abort("Variable not found: " + var);
					}
				}
				escape_seq = "";
				continue;
			}
			else {
				intp->abort("Invalid escape sequence: " + escape_seq);
			}
		}
		else if (escape) {
			escape_seq += ch;
			continue;
		}
		else {
			result += char(ch);
			escape_seq = "";
		}
	}

	return result;
}
void ptm_launch_new_instance_with_program(string program_path)
{
	Util::Run("PTM", "\"" + program_path + "\"");
}
void ptm_clipboard_set(string value)
{
	Util::SendTextToClipboard(value);
}
string ptm_clipboard_get()
{
	return Util::GetTextFromClipboard();
}
void ptm_save_debug_file(string file)
{
	string text = "PTM DEBUG FILE [" + Util::DateTime() + "]\n\n";

	// Variables / constants

	text += "Variables and constants:\n\n";

	if (intp->vars.empty()) {
		text += "\t(empty)\n";
	}
	else {
		for (auto& entry : intp->vars) {
			string name = entry.first;
			string value = entry.second.value;
			bool is_const = entry.second.is_const;
			if (is_const) {
				text += "\tDEF " + name + " = " + value + "\n";
			}
		}
		for (auto& entry : intp->vars) {
			string name = entry.first;
			string value = entry.second.value;
			bool is_const = entry.second.is_const;
			if (!is_const) {
				text += "\tVAR " + name + " = " + value + "\n";
			}
		}
	}
	text += "\n";

	// Arrays

	text += "Arrays:\n\n";

	if (intp->arrays.empty()) {
		text += "\t(empty)\n";
	}
	else {
		for (auto& entry : intp->arrays) {
			string name = entry.first;
			vector<string>& arr = entry.second;
			text += "\tARR " + name + " (length: " + String::ToString(arr.size()) + ")\n";
			for (int i = 0; i < arr.size(); i++) {
				string& element = arr[i];
				text += String::Format("\t\t[%i] %s", i, element.c_str()) + "\n";
			}
		}
	}
	text += "\n";

	// Window

	text += "Window:\n\n";
	text += "\tScreen size: " + String::Format("%i width x %i height", scr.buf_w, scr.buf_h) + "\n";
	text += "\tSize factor: " + String::ToString(scr.wnd_size) + "\n";
	text += "\tPhysical size: " + String::Format("%i width x %i height", scr.wnd_size * scr.buf_w, scr.wnd_size * scr.buf_h) + "\n";
	text += "\tBg. color RGB: " + String::Format("&H%06X", scr.bgcol) + "\n";
	text += "\n";

	// TILE register

	text += "TILE register:\n\n";
	if (working_tile.empty()) {
		text += "\t\tFrames: (empty)\n";
	}
	else {
		text += "\t\tFrames: " + working_tile.to_str() + "\n";
	}
	text += "\t\tProperties:\n";
	auto& prop = working_tile.data;
	if (prop.empty()) {
		text += "\t\t\t(empty)\n";
	}
	else {
		for (auto& prop : working_tile.data.get_all()) {
			text += "\t\t\t" + prop.first + " = " + prop.second + "\n";
		}
	}
	text += "\n";

	// Tilebuffers

	text += "Tile buffers:\n\n";

	for (auto& buf : tilebufs.tilebufs) {
		text += "\tBUF " + buf.id + "\n";
		text += "\t\tOrder: " + String::ToString(buf.order) + "\n";
		text += "\t\tSize: " + String::Format("%i cols x %i rows", buf.get_width(), buf.get_height()) + "\n";
		text += "\t\tLayers: " + String::ToString(buf.get_layer_count()) + "\n";
		text += "\t\tVisible: " + String::Format("%s\n", buf.visible() ? "YES" : "NO");
		text += "\t\tBg. enabled: " + String::Format("%s\n", buf.bg_enabled ? "YES" : "NO");
		text += "\t\tBg. color index: " + String::ToString(buf.get_bgcol()) + "\n";
		t_clip& view = buf.get_viewport();
		text += "\t\tViewport rect: " + String::Format("X1:%i Y1:%i X2:%i Y2:%i", view.x1, view.y1, view.x2, view.y2) + "\n";
		text += "\t\tViewport scroll: " + String::Format("X:%i Y:%i", view.x_offset, view.y_offset) + "\n";
		text += "\t\tSprites owned: " + String::ToString(buf.get_sprites().size()) + "\n";
	}
	text += "\n";

	// Sprites

	text += "Sprites:\n\n";

	if (sprites.get_sprites().empty()) {
		text += "\t(empty)\n";
	}
	else {
		for (auto& entry : sprites.get_sprites()) {
			string id = entry.first;
			t_sprite& spr = entry.second;
			text += "\tSPR " + id + "\n";
			text += "\t\tPosition: " + String::Format("X:%i Y:%i", spr.x, spr.y) + "\n";
			text += "\t\tVisible: " + String::Format("%s\n", spr.visible ? "YES" : "NO");
			auto* buf = spr.get_buffer();
			if (buf) {
				text += "\t\tParent buffer: " + buf->id + "\n";
			}
			else {
				text += "\t\tParent buffer: (none)\n";
			}
			if (spr.tile.empty()) {
				text += "\t\tTile frames: (empty)\n";
			}
			else {
				text += "\t\tTile frames: " + spr.tile.to_str() + "\n";
			}
			text += "\t\tProperties:\n";
			auto& prop = spr.tile.data;
			if (prop.empty()) {
				text += "\t\t\t(empty)\n";
			}
			else {
				for (auto& prop : spr.tile.data.get_all()) {
					text += "\t\t\t" + prop.first + " = " + prop.second + "\n";
				}
			}
		}
	}
	text += "\n";

	// END

	File::WriteText(file, text);
}
