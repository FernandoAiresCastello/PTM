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

	init();
	//run_tests();
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
	bool autoexec = t_filesystem::file_exists(autoexec_file);
	if (!autoexec)
		main_editor.print_welcome();

	while (wnd.is_open()) {
		if (autoexec) {
			autoexec = false;
			load_program(autoexec_file, true);
			run_program_from_immediate_mode();
			intp.print_prompt();
		}
		on_machine_cycle();
	}
}

void PTM::halt()
{
	halted = true;
	while (wnd.is_open() && halted) {
		on_machine_cycle();
	}
}

void PTM::reset(bool new_prg)
{
	halted = false;
	prg_runner.stop();
	delete_all_vars();
	chr.reset();
	pal.reset();
	scr.reset();
	main_editor.reset();

	if (new_prg)
		new_program();
}

void PTM::pause(int frames)
{
	for (int i = 0; i < frames; i++) {
		if (!wnd.is_open())
			break;

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
		scr.show_cursor(true);
		auto_screen_update = true;
	}
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

const t_dict<t_string, t_string>& PTM::get_vars()
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

t_palette& PTM::get_pal() { return pal; }
t_charset& PTM::get_chr() { return chr; }
t_window& PTM::get_wnd() { return wnd; }

t_program& PTM::get_prg()
{
	return prg;
}

void PTM::run_program_from_immediate_mode()
{
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

void PTM::new_program()
{
	prg.lines.clear();
}

void PTM::save_program(const t_string& filename, bool hex)
{
	if (hex)
		filesys.save_program_binary(&prg, filename);
	else
		filesys.save_program_plaintext(&prg, filename);
}

bool PTM::load_program(const t_string& filename, bool hex)
{
	try
	{
		if (hex)
			filesys.load_program_binary(&intp, &prg, filename);
		else
			filesys.load_program_plaintext(&intp, &prg, filename);

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
		list.push_back(t_string::fmt("S%s: %s", keyname.c_str(), value.c_str()));
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

void PTM::create_tilebuf(const t_string& name, int cols, int rows)
{
	tilebufs[name] = std::make_shared<t_tilebuffer>(cols, rows);
}

bool PTM::has_tilebuf(const t_string& name)
{
	return tilebufs.contains(name);
}

t_sptr<t_tilebuffer> PTM::get_tilebuf(const t_string& name)
{
	if (tilebufs.contains(name))
		return tilebufs[name];

	return nullptr;
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
