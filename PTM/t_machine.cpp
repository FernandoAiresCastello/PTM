#include "t_machine.h"

t_machine::t_machine() {
	clear_memory();
	init_memory_map();
}
t_machine::~t_machine() {
}
void t_machine::clear_memory() {
	memory.clear();
	for (int i = 0; i < memory_top; i++) {
		memory.push_back(0);
	}
}
void t_machine::init_memory_map() {
	mmap["scrbuf_ch"] = 0x0000;
}
int t_machine::peek(int addr) {
	return memory[addr];
}
int t_machine::peek(string alias) {
	return memory[mmap[alias]];
}
void t_machine::poke(int addr, int value) {
	memory[addr] = value;
}
void t_machine::poke(string alias, int value) {
	memory[mmap[alias]] = value;
}
void t_machine::update_window(TBufferedWindow* wnd) {
	auto buf = wnd->GetBuffer();
	wnd->Update();
}
