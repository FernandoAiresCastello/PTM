#include "t_compiler.h"
#include "t_program.h"
#include "t_source_line.h"

void t_compiler::compile(t_program* prg) {
	prg->lines.clear();
	for (auto& srcline : prg->src_lines) {
		compile_line(prg, &srcline);
	}
}
void t_compiler::compile_line(t_program* prg, t_source_line* srcline) {
	auto src = srcline->src;
	auto ixSpace = String::FindFirst(src, ' ');
	auto cmd = ixSpace >= 0 ? String::Trim(src.substr(0, ixSpace)) : src;
	auto raw_args = ixSpace >= 0 ? String::Trim(src.substr(ixSpace)) : "";
	std::vector<string> args;
	bool quote = false;
	string arg;

	for (int i = 0; i < raw_args.length(); i++) {
		char ch = raw_args[i];
		if (ch == '\"') {
			quote = !quote;
		}
		if (ch == ',' || i == raw_args.length() - 1) {
			if (ch != ',') arg += ch;
			args.push_back(String::Trim(arg));
			arg = "";
		} else {
			arg += ch;
		}
	}
	t_program_line line;
	line.src = srcline;
	line.cmd = cmd;
	line.args = args;
	prg->lines.push_back(line);
}
