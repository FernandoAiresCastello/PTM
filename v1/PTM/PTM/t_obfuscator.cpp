#include "t_obfuscator.h"

std::vector<string> t_obfuscator::xor_encrypt(std::vector<string>* src) {
	std::vector<string> dest;
	for (auto& srcline : *src) {
		dest.push_back(Util::XorEncrypt(srcline, xor_key));
	}
	return dest;
}
void t_obfuscator::xor_decrypt(std::vector<string>* src, std::vector<string>* dest) {
	dest->clear();
	for (auto& srcline : *src) {
		dest->push_back(Util::XorDecrypt(srcline, xor_key));
	}
}
