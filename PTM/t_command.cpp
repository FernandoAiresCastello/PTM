#include "t_command.h"
#include "t_interpreter.h"
#include "t_machine.h"
#include "t_program.h"

t_command::t_command(t_interpreter* intp) {
	this->intp = intp;
	machine = intp->machine;
}
bool t_command::execute(string& cmd, t_params& args) {
	     if (cmd == "MDUMP")	save_memory_dump(args);
	else if (cmd == "HALT")		halt(args);
	else if (cmd == "EXIT")		exit(args);
	else if (cmd == "GOTO")		branch(args);
	else if (cmd == "PTR")		define_alias(args);
	else if (cmd == "POKE")		poke(args);
	else if (cmd == "INC")		increment_memory_value(args);
	else if (cmd == "PTR+")		increment_alias_address(args);
	else if (cmd == "PTR-")		decrement_alias_address(args);

	else return false;
	return true;
}
void t_command::save_memory_dump(t_params& arg) {
	intp->argc(arg, 0, 2);
	int first_addr = 0;
	int last_addr = t_machine::memory_top - 1;
	if (arg.size() == 1) {
		first_addr = intp->require_number(arg[0]);
	}
	else if (arg.size() == 2) {
		first_addr = intp->require_number(arg[0]);
		last_addr = intp->require_number(arg[1]);
	}

	std::vector<string> lines;
	for (int addr = first_addr; addr <= last_addr; addr++) {
		int val = machine->peek(addr);
		int ch = val >= ' ' && val < 0x7f ? val : ' ';
		string line = String::Format(
			" 0x%04X (%05i):  %c  %i", addr, addr, ch, val);

		lines.push_back(line);
	}

	File::WriteLines("memdump.txt", lines);
}
void t_command::halt(t_params& arg) {
	intp->argc(arg, 0);
	intp->halted = true;
}
void t_command::exit(t_params& arg) {
	intp->argc(arg, 0);
	intp->running = false;
}
void t_command::branch(t_params& arg) {
	intp->argc(arg, 1);
	string label = intp->require_label(arg[0]);
	if (!label.empty()) {
		intp->cur_line_ix = intp->prg->labels[label];
		intp->branched = true;
	}
}
void t_command::define_alias(t_params& arg) {
	if (!intp->argc(arg, 2)) return;

	if (arg[0].type != t_param_type::address_alias) {
		intp->abort("Alias expected");
		return;
	}
	if (arg[1].type == t_param_type::address_alias) {
		if (intp->has_address_alias(arg[1].address_alias)) {
			machine->mmap[arg[0].address_alias] = intp->get_address_with_alias(arg[1].address_alias);
		} else {
			intp->abort("Undefined alias: " + arg[1].address_alias);
		}
	} else {
		machine->mmap[arg[0].address_alias] = arg[1].numeric_value;
	}
}
void t_command::poke(t_params& arg) {
	intp->argc(arg, 2);
	if (arg[1].type == t_param_type::string) {
		poke_string(arg);
	} else {
		int address = intp->require_adress_or_alias(arg[0]);
		if (address != t_machine::illegal_address) {
			int value = intp->require_number(arg[1]);
			machine->poke(address, value);
		}
	}
}
void t_command::poke_string(t_params& arg) {
	intp->argc(arg, 2);
	int address = intp->require_adress_or_alias(arg[0]);
	if (address != t_machine::illegal_address) {
		string value = intp->require_string(arg[1]);
		for (char& ch : value) {
			machine->poke(address, ch);
			address++;
			if (address >= t_machine::memory_top) {
				break;
			}
		}
		machine->poke(address, 0);
	}
}
void t_command::add_to_memory_value(t_params& arg) {
	intp->argc(arg, 2);
	int address = intp->require_adress_or_alias(arg[0]);
	int value = intp->require_number(arg[1]);
	machine->poke(address, machine->peek(address) + value);
}
void t_command::increment_memory_value(t_params& arg) {
	intp->argc(arg, 1);
	int address = intp->require_adress_or_alias(arg[0]);
	machine->poke(address, machine->peek(address) + 1);
}
void t_command::increment_alias_address(t_params& arg) {
	intp->argc(arg, 1, 2);
	intp->require_aliased_address(arg[0]);
	if (arg.size() == 1) {
		machine->mmap[arg[0].address_alias] = machine->mmap[arg[0].address_alias] + 1;
	} else if (arg.size() == 2) {
		int value = intp->require_number(arg[1]);
		machine->mmap[arg[0].address_alias] = machine->mmap[arg[0].address_alias] + value;
	}
}
void t_command::decrement_alias_address(t_params& arg) {
	intp->argc(arg, 1, 2);
	intp->require_aliased_address(arg[0]);
	if (arg.size() == 1) {
		machine->mmap[arg[0].address_alias] = machine->mmap[arg[0].address_alias] - 1;
	} else if (arg.size() == 2) {
		int value = intp->require_number(arg[1]);
		machine->mmap[arg[0].address_alias] = machine->mmap[arg[0].address_alias] - value;
	}
}
