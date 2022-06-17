#include "t_game.h"

t_game::t_game() {
    clear_memory();
}
bool t_game::has_address_alias(string alias) {
    return address_alias.find(alias) != address_alias.end();
}
int t_game::get_address_with_alias(string alias) {
    return has_address_alias(alias) ? address_alias[alias] : ILLEGAL_ADDRESS;
}
int t_game::peek_address(int address) {
    return memory[address];
}
int t_game::peek_address_with_alias(string alias) {
    return memory[get_address_with_alias(alias)];
}
void t_game::poke_address(int address, int value) {
    memory[address] = value;
}
void t_game::poke_address_with_alias(string alias, int value) {
    if (has_address_alias(alias)) {
        memory[get_address_with_alias(alias)] = value;
    }
}
void t_game::clear_memory() {
    for (int i = 0; i < MEMORY_TOP; i++) {
        memory[i] = 0;
    }
}
string t_game::get_string_from_address_with_alias(string alias) {
    return get_string_from_address(get_address_with_alias(alias));
}
string t_game::get_string_from_address(int start_address) {
    string str = "";
    int addr = start_address;
    bool scanning = true;
    while (scanning) {
        int ch = memory[addr];
        if (ch <= 0) {
            scanning = false;
        } else if (ch <= 255) {
            str += (char)ch;
        }
        addr++;
        if (addr >= MEMORY_TOP) {
            scanning = false;
        }
    }
    return str;
}
