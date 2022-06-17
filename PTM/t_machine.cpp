#include "t_machine.h"

t_machine::t_machine() {
}
t_machine::~t_machine() {
}
void t_machine::clear_memory() {
	for (int i = 0; i < MEMORY_TOP; i++) {
		memory[i] = 0;
	}
}
int t_machine::peek(int addr) {
	return memory[addr];
}
void t_machine::poke(int addr, int value) {
	memory[addr] = value;
}
void t_machine::update_window(TBufferedWindow* wnd) {
	wnd->Update();
}
