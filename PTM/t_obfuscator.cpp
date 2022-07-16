#include "t_obfuscator.h"
#include "base64.h"

std::vector<string> t_obfuscator::encrypt(std::vector<string>* src) {
	std::vector<string> dest;
	for (auto& srcline : *src) {
		string dstline = base64_encode(srcline);
		dest.push_back(dstline);
	}
	return dest;
}
void t_obfuscator::decrypt(std::vector<string>* src, std::vector<string>* dest) {
	dest->clear();
	for (auto& srcline : *src) {
		string dstline = base64_decode(srcline);
		dest->push_back(dstline);
	}
}
