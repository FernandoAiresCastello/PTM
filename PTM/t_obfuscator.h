#pragma once
#include "common.h"

struct t_obfuscator {
	static const char xor_key = '@';
	static std::vector<string> xor_encrypt(std::vector<string>* src);
	static void xor_decrypt(std::vector<string>* src, std::vector<string>* dest);
};
