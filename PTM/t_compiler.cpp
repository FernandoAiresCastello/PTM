#include "t_compiler.h"
#include "t_program.h"
#include "t_program_line.h"

#define TOKEN_COMMENT "'"
#define TOKEN_LABEL ":"

void t_compiler::run(t_program* prg) {
	prg->lines.clear();
	prg->labels.clear();
	for (auto& srcline : prg->src_lines) {
		t_program_line new_line;
		bool must_add_line = compile(prg, &new_line, srcline);
		if (must_add_line) {
			prg->lines.push_back(new_line);
		}
	}
}
bool t_compiler::compile(t_program* prg, t_program_line* new_line, string src_line) {
	if (is_comment(src_line)) {
		return false;
	}
	if (is_label(src_line)) {
		prg->labels[String::Skip(src_line, 1)] = prg->lines.size();
		return false;
	}
	new_line->src = src_line;
	auto ixSpace = String::FindFirst(src_line, ' ');
	new_line->cmd = ixSpace >= 0 ? String::Trim(src_line.substr(0, ixSpace)) : src_line;
	auto raw_args = ixSpace >= 0 ? String::Trim(src_line.substr(ixSpace)) : "";
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
		new_line->params.push_back(param);
	}

	return true;
}
bool t_compiler::is_comment(string src) {
	return String::StartsWith(src, TOKEN_COMMENT);
}
bool t_compiler::is_label(string src) {
	return String::StartsWith(src, TOKEN_LABEL);
}
