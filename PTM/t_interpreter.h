#pragma once
#include "common.h"
#include "t_param.h"

struct t_program;
struct t_program_line;
struct t_machine;
struct t_command;

struct t_interpreter {
	std::vector<string> errors;
	t_interpreter();
	bool has_user_break();
	void run(t_program* prg, t_machine* machine, TBufferedWindow* wnd);
private:
	friend struct t_command;
	TBufferedWindow* wnd;
	TTileBuffer* wnd_buf;
	t_machine* machine;
	t_program* prg;
	t_program_line* cur_line;
	bool running;
	bool halted;
	bool user_break;
	int cur_line_ix;
	bool branched;
	t_command* cmd;
	std::stack<int> callstack;
	
	void execute_current_line();
	void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt);
	void abort(string error);
	bool argc(t_params& arg, int expected);
	bool argc(t_params& arg, int min, int max);
	int require_number(t_param& arg);
	string require_label(t_param& arg);
	int require_adress_or_alias(t_param& arg);
	int require_aliased_address(t_param& arg);
	string require_string(t_param& arg);

	std::map<string, int> address_alias;
	bool has_address_alias(string alias);
	int get_address_with_alias(string alias);
	int peek_address_with_alias(string alias);
	void poke_address_with_alias(string alias, int value);
	string get_string_from_address_with_alias(string alias);
	string get_string_from_address(int start_address);
};
