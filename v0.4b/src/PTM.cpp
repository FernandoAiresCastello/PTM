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

t_window wnd;
t_keyboard kb;
t_charset chr;
t_palette pal;
t_screen scr;
t_main_editor main_editor;
t_interpreter intp;
t_tile tilereg;
t_program prg;
t_program_runner prg_runner;

int wnd_size = 3;

void PTM::run()
{
	if (running)
		return;

	running = true;
	halted = false;
	tilereg.set_empty();
	prg.lines.clear();

	init();
	run_tests();
	run_main();
}

void PTM::exit()
{
	wnd.close();
}

void PTM::init()
{
	wnd.open(title, wnd_size);

	scr.set_window(&wnd);
	scr.set_charset(&chr);
	scr.set_palette(&pal);

	intp.init(this, &scr, &kb);
	main_editor.init(this, &scr, &kb, &intp);
}

void PTM::run_main()
{
	main_editor.print_welcome();

	while (wnd.is_open()) {
		on_machine_cycle();
	}
}

void PTM::halt()
{
	halted = true;
	while (wnd.is_open()) {
		on_machine_cycle();
	}
}

void PTM::pause(int frames)
{
	for (int i = 0; i < frames; i++) {
		if (!wnd.is_open())
			break;

		on_machine_cycle();
	}
}

void PTM::debug(t_string msg)
{
	wnd.set_title(msg);
}

void PTM::on_machine_cycle() const
{
	scr.on_every_machine_cycle();
	wnd.update();

	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		wnd.close();
	}
	else if (e.type == SDL_KEYDOWN) {
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_RETURN && kb.alt()) {
			wnd.toggle_fullscreen();
		}
		else if (key == SDLK_ESCAPE) {
			wnd.close();
		}
		else if (!kb.alt() && !halted) {
			kb.key = key;
			main_editor.on_keydown();
		}
	}
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

t_palette& PTM::get_pal() { return pal; }
t_charset& PTM::get_chr() { return chr; }
t_window& PTM::get_wnd() { return wnd; }
t_tile& PTM::get_tilereg() { return tilereg; }
void PTM::set_tilereg(const t_tile& tile) { tilereg = tile; }

t_program& PTM::get_prg()
{
	return prg;
}

void PTM::run_program()
{
	prg_runner.run(&prg, &intp);
}

void PTM::end_program()
{
	prg_runner.stop();
}
