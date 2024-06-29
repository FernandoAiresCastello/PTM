#pragma once
#include "t_tile.h"
#include "t_string.h"
#include "t_list.h"
#include "t_dict.h"
#include "t_token.h"
#include "t_charset.h"
#include "t_palette.h"
#include "t_window.h"
#include "t_program.h"
#include "t_program_line.h"

class PTM
{
public:
	const t_string title = "PTM - Programmable Tile Machine";

	void run();
	void exit();
	void halt();
	void pause(int frames);
	void on_machine_cycle();
	bool is_window_open() const;
	void debug(t_string msg);
	void save_program_line(t_program_line& line);
	bool delete_program_line(int line_nr);
	void set_var(const t_string& var, const t_string& value);
	void set_var(const t_string& var, int value);
	const t_string& get_var_str(const t_string& var);
	int get_var_num(const t_string& var);
	const t_dict<t_string, t_string>& get_vars();
	bool has_var(const t_string& var);
	t_palette& get_pal();
	t_charset& get_chr();
	t_window& get_wnd();
	t_tile& get_tilereg();
	void set_tilereg(const t_tile& tile);
	t_program& get_prg();
	void run_program();
	void end_program();
	bool has_program_label(const t_string& label);
	void goto_program_label(const t_string& label);

private:
	bool running = false;
	bool halted = false;
	t_dict<t_string, t_string> vars;

	void init();
	void run_tests();
	void run_graphics_test();
	void run_main();
};
