#include <stdexcept>
#include "PTM.h"
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
#include "t_filesystem.h"

int wnd_size = 3;
t_window wnd;
t_main_editor main_editor;
t_interpreter intp;
t_program prg;
t_program_runner prg_runner;
t_filesystem filesys;
t_keyboard kb;
t_charset chr;
t_palette pal;
t_screen scr(256, t_window::rows - 2);

void PTM::run()
{
	if (running)
		return;

	running = true;
	halted = false;
	tilereg.set_empty();
	prg.lines.clear();
	sound_gen.set_volume(t_sound_mml::max_volume / 5);

	init();
	run_main();
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
	main_editor.init(this, &scr, &kb, &intp);
}

void PTM::run_main()
{
	sound_gen.beep(1450, 50);

	bool autoexec = t_filesystem::file_exists(autoexec_file);
	if (!autoexec)
		main_editor.print_welcome(true);

	while (wnd.is_open()) {
		if (autoexec) {
			autoexec = false;
			load_program(autoexec_file, true);
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
	delete_all_tables();
	delete_all_sprites();
	new_program();
	main_editor.reset();
	main_editor.print_welcome(false);
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
				main_editor.on_keydown();
			}
		}
	}
}

void PTM::on_escape_key_pressed()
{
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

void PTM::set_var(const t_string& var, const t_string& value)
{
	vars[var] = value;
}

void PTM::set_var(const t_string& var, int value)
{
	vars[var] = value;
}

const t_string& PTM::get_var_str(const t_string& var)
{
	return vars[var];
}

int PTM::get_var_num(const t_string& var)
{
	return vars[var].to_int();
}

const t_namespace<t_string>& PTM::get_vars()
{
	return vars;
}

bool PTM::has_var(const t_string& var)
{
	return vars.contains(var);
}

void PTM::delete_all_vars()
{
	vars.clear();
}

void PTM::delete_all_tables()
{
	tables.clear();
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
	last_program_filename = "";
}

void PTM::save_program(const t_string& filename, bool hex)
{
	if (hex)
		filesys.save_program_binary(&prg, filename);
	else
		filesys.save_program_plaintext(&prg, filename);

	last_program_filename = filename.to_upper();
}

bool PTM::load_program(const t_string& filename, bool hex)
{
	try
	{
		if (hex)
			filesys.load_program_binary(&intp, &prg, filename);
		else
			filesys.load_program_plaintext(&intp, &prg, filename);
		
		if (!prg.lines.empty())
			last_program_filename = filename.to_upper();

		return !prg.lines.empty();
	}
	catch (std::runtime_error error)
	{
		return false;
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

bool PTM::set_function_key(const t_string& keyname, const t_string& value)
{
	bool shifted = false;
	SDL_Keycode keycode = SDLK_UNKNOWN;

	if (keyname.starts_with("S") || keyname.starts_with("s")) {
		shifted = true;
		t_string&& unshifted_keyname = keyname.skip(1);
		keycode = kb.get_keycode_by_name(unshifted_keyname);
	}
	else {
		keycode = kb.get_keycode_by_name(keyname);
	}

	if (keycode == SDLK_UNKNOWN)
		return false;

	if (shifted)
		main_editor.function_keys_shifted[keycode] = value;
	else
		main_editor.function_keys[keycode] = value;

	return true;
}

t_list<t_string> PTM::list_function_keys()
{
	t_list<t_string> list;
	for (auto& entry : main_editor.function_keys) {
		auto&& keyname = kb.get_name_by_keycode(entry.first);
		auto& value = entry.second;
		list.push_back(t_string::fmt("%s: %s", keyname.c_str(), value.c_str()));
	}
	for (auto& entry : main_editor.function_keys_shifted) {
		auto&& keyname = kb.get_name_by_keycode(entry.first);
		auto& value = entry.second;
		list.push_back(t_string::fmt("s%s: %s", keyname.c_str(), value.c_str()));
	}
	return list;
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

void PTM::add_sprite(const t_string& name, int x, int y, bool visible)
{
	sprites[name] = scr.add_sprite(tilereg, t_pos(x, y));
	sprites[name]->set_visible(visible);
}

t_sprite_ptr PTM::get_sprite(const t_string& name)
{
	if (sprites.contains(name))
		return sprites[name];

	return nullptr;
}

void PTM::delete_all_sprites()
{
	scr.delete_all_sprites();
	sprites.clear();
}

const t_string& PTM::get_last_program_filename() const
{
	return last_program_filename;
}

void PTM::autosave_program_file()
{
	filesys.save_program_binary(&prg, autosave_file);
}

void PTM::create_table(const t_string& name, int cols, int rows)
{
	tables[name].init(cols, rows);
}

bool PTM::has_table(const t_string& name)
{
	return tables.contains(name);
}

t_table& PTM::get_table(const t_string& name)
{
	return tables[name];
}

const t_namespace<t_table>& PTM::get_tables()
{
	return tables;
}

void PTM::save_tilereg(const t_string& name)
{
	tile_presets[name] = tilereg;
}

void PTM::load_tilereg(const t_string& name)
{
	tilereg = tile_presets[name];
}

bool PTM::has_tilereg(const t_string& name)
{
	return tile_presets.contains(name);
}

int PTM::find_program_label(const t_string& label)
{
	return prg.find_label(label);
}

t_sound_mml& PTM::get_sound_gen()
{
	return sound_gen;
}
