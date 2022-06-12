#include "t_compiler.h"
#include "t_program.h"
#include "t_source_line.h"
#include "t_program_line.h"

void t_compiler::run(t_program* prg) {
	prg->lines.clear();
	for (auto& srcline : prg->src_lines) {
		t_program_line line;
		parse_src_line(prg, &srcline, &line);
		compile(&line);
		prg->lines.push_back(line);
	}
}
void t_compiler::parse_src_line(t_program* prg, t_source_line* srcline, t_program_line* line) {
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

	line->src = srcline;
	line->cmd = cmd;
	line->args = args;
}
void t_compiler::compile(t_program_line* line) {
	line->code.push_back(0xff);
}
