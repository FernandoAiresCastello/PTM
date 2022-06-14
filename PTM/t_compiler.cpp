#include "t_compiler.h"
#include "t_program.h"
#include "t_source_line.h"
#include "t_program_line.h"

#define TOKEN_COMMENT "'"
#define TOKEN_LABEL ":"

void t_compiler::run(t_program* prg) {
	prg->lines.clear();
	prg->labels.clear();
	for (auto& srcline : prg->src_lines) {
		t_program_line line;
		compile(prg, &srcline, &line);
		if (!line.ignore) {
			prg->lines.push_back(line);
		}
	}
}
void t_compiler::compile(t_program* prg, t_source_line* srcline, t_program_line* line) {
	auto src = srcline->src;
	if (is_comment(src)) {
		line->ignore = true;
		return;
	}
	if (is_label(src)) {
		prg->labels[String::Skip(src, 1)] = prg->lines.size();
		line->ignore = true;
		return;
	}
	line->src = srcline;
	auto ixSpace = String::FindFirst(src, ' ');
	line->cmd = ixSpace >= 0 ? String::Trim(src.substr(0, ixSpace)) : src;
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

	for (auto& arg : args) {
		t_param param;
		// todo
		line->params.push_back(param);
	}
}
bool t_compiler::is_comment(string src) {
	return String::StartsWith(src, TOKEN_COMMENT);
}
bool t_compiler::is_label(string src) {
	return String::StartsWith(src, TOKEN_LABEL);
}
