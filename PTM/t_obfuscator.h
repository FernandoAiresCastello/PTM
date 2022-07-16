#pragma once
#include "common.h"

struct t_obfuscator {
	static std::vector<string> encrypt(std::vector<string>* src);
	static void decrypt(std::vector<string>* src, std::vector<string>* dest);
};
