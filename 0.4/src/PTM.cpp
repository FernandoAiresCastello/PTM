#include <stdexcept>
#include "PTM.h"
#include "PTML_errors.h"
#include "t_tests.h"
#include "t_window.h"
#include "t_keyboard.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_tilebuffer.h"
#include "t_screen.h"
#include "t_util.h"
#include "t_main_editor.h"
#include "t_interpreter.h"
#include "t_program.h"
#include "t_program_line.h"
#include "t_program_runner.h"
#include "t_program_editor.h"
#include "t_filesystem.h"

int wnd_size = 3;
t_window wnd;
t_main_editor main_editor;
t_program_editor program_editor;
t_interpreter intp;
t_program prg;
t_program_runner prg_runner;
t_keyboard kb;
t_charset chr;
t_palette pal;
t_sound snd;
t_screen scr(256, t_window::rows - 2);
const t_string empty_string = "";

void PTM::run(const char* initial_program)
{
	if (running)
		return;

	if (initial_program)
		enable_autosave = false;

	running = true;
	halted = false;
	tilereg.set_empty();
	prg.lines.clear();
	snd.set_volume(10);

	init();
	run_main(initial_program);
}

void PTM::exit()
{
	wnd.close();
	SDL_Quit();
}

void PTM::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	wnd.open(title, wnd_size);
	
	kb.init();

	scr.set_window(&wnd);
	scr.set_charset(&chr);
	scr.set_palette(&pal);

	intp.init(this, &scr, &kb);
	program_editor.init(this, &scr, &kb);
	main_editor.init(this, &scr, &kb, &intp);
}

void PTM::run_main(const char* initial_program)
{
	bool autoexec = t_filesystem::has_autoexec_file();
	bool has_initial_prog = initial_program != nullptr;

	if (!autoexec && !has_initial_prog) {
		snd.alert();
		main_editor.print_welcome(true);
	}

	while (wnd.is_open()) {
		if (has_initial_prog) {
			has_initial_prog = false;
			load_program_absolute_path(initial_program);
			run_program_from_immediate_mode();
			intp.print_prompt();
		}
		else if (autoexec) {
			autoexec = false;
			load_program(t_filesystem::get_autoexec_file());
			run_program_from_immediate_mode();
			intp.print_prompt();
		}
		on_machine_cycle();
	}

	on_exit();
}

void PTM::halt()
{
	halted = true;
	while (wnd.is_open() && halted) {
		on_machine_cycle();
	}
}

void PTM::reset()
{
	autosave_program_file();

	halted = false;
	prg_runner.stop();
	chr.reset();
	pal.reset();
	scr.reset();
	tilereg.set_empty();
	delete_all_vars();
	new_program();
	main_editor.reset();
	main_editor.print_welcome(false);
	program_editor.reset();
}

void PTM::pause(int frames)
{
	for (int i = 0; i < frames; i++) {
		if (!wnd.is_open() ||
			!prg_runner.is_running() ||
			prg_runner.is_stopping()) {

			break;
		}

		if (!auto_screen_update)
			refresh_screen();

		on_machine_cycle();
	}
}

void PTM::debug(const t_string& msg)
{
	wnd.set_title(msg);
}

void PTM::on_machine_cycle()
{
	if (!wnd.is_open())
		return;

	if (program_editor.active)
		program_editor.draw_program();

	if (auto_screen_update)
		refresh_screen();

	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		wnd.close();
	}
	else if (e.type == SDL_KEYDOWN) {
		SDL_Keycode& key = e.key.keysym.sym;
		if (key == SDLK_RETURN && kb.alt()) {
			wnd.toggle_fullscreen();
		}
		else if (key == SDLK_ESCAPE) {
			on_escape_key_pressed();
		}
		else if (!kb.alt() && !halted) {
			kb.push_key(key);
			if (!prg_runner.is_running()) {
				if (main_editor.active)
					main_editor.on_keydown();
				if (program_editor.active)
					program_editor.on_keydown();
			}
		}
	}
}

void PTM::on_escape_key_pressed()
{
	if (!enable_user_break)
		return;

	if (halted) {
		halted = false;
	}
	if (prg_runner.is_running()) {
		prg_runner.stop();
		intp.on_user_interrupt(prg_runner.get_current_line());
	}
}

void PTM::on_exit()
{
	autosave_program_file();
}

SDL_Keycode PTM::await_keypress()
{
	SDL_Keycode key_pressed = 0;
	bool awaiting = true;

	while (awaiting && wnd.is_open()) {
		if (auto_screen_update)
			refresh_screen();

		SDL_Event e;
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			wnd.close();
		}
		else if (e.type == SDL_KEYDOWN) {
			SDL_Keycode& key = e.key.keysym.sym;
			if (key == SDLK_RETURN && kb.alt()) {
				wnd.toggle_fullscreen();
			}
			else if (!kb.alt()) {
				key_pressed = key;
				awaiting = false;
			}
		}
	}

	return key_pressed;
}

void PTM::refresh_screen()
{
	scr.refresh();
	wnd.refresh();
}

bool PTM::is_window_open() const
{
	return wnd.is_open();
}

void PTM::run_tests()
{
	t_tests tests;
	tests.run();
}

void PTM::run_graphics_test()
{
	int i = 0;
	for (int y = 1; y < 1 + 16; y++) {
		for (int x = 1; x < 1 + 16; x++) {
			scr.set_tile(t_tile(0, i, i, t_tileflags()), x, y);
			i++;
		}
	}

	i = 0;
	for (int y = 1; y < 1 + 16; y++) {
		for (int x = 20; x < 20 + 16; x++) {
			scr.set_tile(t_tile(i, 15, 0, t_tileflags()), x, y);
			i++;
		}
	}

	halt();
}

void PTM::save_program_line(t_program_line& line)
{
	prg.set_line(line);
}

bool PTM::delete_program_line(int line_nr)
{
	return prg.delete_line(line_nr);
}

void PTM::set_var(const t_param& param, int value, t_string& out_error)
{
	set_var(param, t_string(value), out_error);
}

void PTM::set_var(const t_param& param, const t_string& value, t_string& out_error)
{
	if (param.is_ident()) {
		vars[param.string_val] = value;
	}
	else if (param.is_array()) {
		set_array(param.array_ref, value, out_error);
	}
	else {
		out_error = PTML::err.illegal_argument;
	}
}

void PTM::set_array(const t_array_ref& ref, const t_string& value, t_string& out_error)
{
	if (!has_array(ref.arr_name)) {
		out_error = PTML::err.undefined_array;
		return;
	}

	int&& index = ref.literal ? ref.arr_subscript_lit : get_var_num(ref.arr_subscript_var);

	if (index >= arrays[ref.arr_name].size()) {
		out_error = PTML::err.subscript_out_of_range;
		return;
	}

	arrays[ref.arr_name][index] = value;
}

int PTM::get_var_num(const t_param& param, t_string& out_error)
{
	return get_var_str(param, out_error).to_int();
}

int PTM::get_var_num(const t_string& varname)
{
	return vars[varname].to_int();
}

const t_string& PTM::get_var_str(const t_param& param, t_string& out_error)
{
	if (param.is_ident())
		return vars[param.string_val];
	else if (param.is_array())
		return get_array_element(param.array_ref, out_error);

	out_error = PTML::err.illegal_argument;

	return empty_string;
}

const t_string& PTM::get_var_str(const t_string& varname)
{
	return vars[varname];
}

const t_namespace<t_string>& PTM::get_vars()
{
	return vars;
}

bool PTM::has_var(const t_string& var)
{
	return vars.contains(var);
}

bool PTM::has_array(const t_string& var)
{
	return arrays.contains(var);
}

void PTM::create_array(const t_array_ref& array_ref, t_string& out_error)
{
	int&& length = array_ref.literal ? array_ref.arr_subscript_lit : get_var_num(array_ref.arr_subscript_var);

	if (length > 0)
		arrays[array_ref.arr_name] = t_list<t_string>(length);
	else
		out_error = PTML::err.illegal_argument;
}

const t_string& PTM::get_array_element(const t_array_ref& ref, t_string& out_error)
{
	if (!has_array(ref.arr_name)) {
		out_error = PTML::err.undefined_array;
		return empty_string;
	}

	int&& index = ref.literal ? ref.arr_subscript_lit : get_var_num(ref.arr_subscript_var);

	if (index >= arrays[ref.arr_name].size()) {
		out_error = PTML::err.subscript_out_of_range;
		return empty_string;
	}

	return arrays[ref.arr_name][index];
}

int PTM::get_array_length(const t_string& array_name, t_string& out_error)
{
	if (!has_array(array_name)) {
		out_error = PTML::err.undefined_array;
		return 0;
	}
	return arrays[array_name].size();
}

void PTM::delete_all_vars()
{
	vars.clear();
	arrays.clear();
}

t_palette& PTM::get_pal() { return pal; }
t_charset& PTM::get_chr() { return chr; }
t_screen& PTM::get_screen() { return scr; }
t_window& PTM::get_wnd() { return wnd; }

t_program& PTM::get_prg()
{
	return prg;
}

void PTM::run_program_from_immediate_mode()
{
	autosave_program_file();

	prg_runner.run_program_from_immediate_mode(this, &prg, &intp);
}

void PTM::run_program_from_another_program()
{
	prg_runner.run_program_from_another_program();
}

bool PTM::has_new_program_loaded_at_runtime()
{
	return prg_runner.has_new_program_loaded_at_runtime();
}

void PTM::end_program()
{
	prg_runner.stop();
}

void PTM::on_program_end()
{
	scr.show_cursor(true);
	auto_screen_update = true;
}

void PTM::new_program()
{
	prg.lines.clear();
	set_last_program_filename("");
}

void PTM::save_program(const t_string& filename)
{
	t_string actual_filename = filename.to_upper();
	if (!actual_filename.ends_with(PROGRAM_FILE_EXT))
		actual_filename = filename + PROGRAM_FILE_EXT;

	t_filesystem::save_program_plaintext(&prg, t_string(USER_ROOT) + actual_filename);
	set_last_program_filename(actual_filename);
}

bool PTM::load_program(const t_string& filename)
{
	t_string actual_filename = filename.to_upper();
	if (!actual_filename.ends_with(PROGRAM_FILE_EXT))
		actual_filename = filename + PROGRAM_FILE_EXT;

	return load_program_absolute_path(t_string(USER_ROOT) + actual_filename);
}

bool PTM::load_program_absolute_path(const t_string& path)
{
	try
	{
		t_filesystem::load_program_plaintext(&intp, &prg, path);
		if (!prg.lines.empty()) {
			set_last_program_filename(path);
		}

		return !prg.lines.empty();
	}
	catch (std::runtime_error error)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PTM - Error loading program",
			t_string::fmt("%s\n\n%s", error.what(), path.c_str()).c_str(), nullptr);

		return false;
	}
}

void PTM::set_last_program_filename(const t_string& path)
{
	int last_slash_ix = path.last_index_of("/");
	if (last_slash_ix >= 0) {
		t_string filename = path.substr(last_slash_ix + 1);
		last_program_filename = filename.to_upper();
	}
	else {
		last_program_filename = path;
	}
}

bool PTM::has_program_label(const t_string& label)
{
	return prg_runner.labels.contains(label);
}

void PTM::goto_program_label(const t_string& label)
{
	prg_runner.go_to(label);
}

void PTM::call_program_label(const t_string& label)
{
	prg_runner.call(label);
}

bool PTM::is_callstack_empty()
{
	return prg_runner.callstack.empty();
}

void PTM::return_from_call()
{
	prg_runner.return_from_call();
}

void PTM::renumber_program(int interval)
{
	prg.renumber_lines(interval);
}

int PTM::get_last_key() const
{
	int key = kb.last_key;
	kb.last_key = 0;
	return key;
}

void PTM::flush_keyboard()
{
	kb.flush();
}

bool PTM::is_key_pressed(int scancode)
{
	return kb.is_pressed((SDL_Scancode)scancode);
}

bool PTM::is_key_pressed(const t_string& keyname)
{
	return kb.is_pressed(keyname);
}

t_string PTM::input_string(const t_string& prompt, int maxlen)
{
	t_string value;
	bool escaped = false;
	const int initial_x = scr.csrx();

	if (!prompt.empty())
		scr.print_string(prompt);

	while (wnd.is_open()) {
		SDL_Keycode key = await_keypress();
		if (key == SDLK_RETURN) {
			scr.newline();
			escaped = false;
			break;
		}
		else if (key == SDLK_ESCAPE) {
			on_escape_key_pressed();
			escaped = true;
			break;
		}
		else if (key == SDLK_BACKSPACE) {
			if (scr.csrx() > initial_x) {
				scr.move_cursor_dist(-1, 0);
				scr.set_blank_tile_at_csr();
				value = value.substr(0, value.length() - 2);
			}
		}
		else {
			if (value.length() < maxlen) {
				int ch = kb.keycode_to_char(key);
				if (ch > 0) {
					scr.print_char(ch);
					value += ch;
				}
			}
		}
	}

	return value;
}

void PTM::autosave_program_file() const
{
	if (enable_autosave)
		t_filesystem::autosave_program(&prg);
}

int PTM::find_program_label(const t_string& label)
{
	return prg.find_label(label);
}

t_sound& PTM::get_sound()
{
	return snd;
}

const t_string& PTM::get_last_program_filename() const
{
	return last_program_filename;
}

void PTM::draw_user_buffer(int x, int y, int w, int h, int xoff, int yoff)
{
	auto& tiles = usr_tilebuf.get_tiles();

	int buf_x = 0;
	int buf_y = 0;

	for (int scr_y = y; scr_y <= y + h; scr_y++) {
		for (int scr_x = x; scr_x <= x + w; scr_x++) {
			int&& cur_buf_x = buf_x + xoff;
			int&& cur_buf_y = buf_y + yoff;
			if (cur_buf_x >= 0 && cur_buf_y >= 0 && cur_buf_x < usr_tilebuf.width() && cur_buf_y < usr_tilebuf.height()) {
				auto& tile = usr_tilebuf.get_ref(cur_buf_x, cur_buf_y);
				scr.set_tile(tile, scr_x, scr_y);
			}
			buf_x++;
		}
		buf_y++;
		buf_x = 0;
	}
}
