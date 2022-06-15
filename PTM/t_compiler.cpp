#include "t_compiler.h"
#include "t_program.h"
#include "t_program_line.h"

#define TOKEN_COMMENT ";"
#define TOKEN_LABEL ":"

void t_compiler::run(t_program* prg) {
	errors.clear();
	prg->lines.clear();
	prg->labels.clear();
	int src_line_nr = 1;
	for (auto& srcline : prg->src_lines) {
		t_program_line new_line;
		bool must_add_line = compile(prg, &new_line, srcline, src_line_nr);
		if (must_add_line) {
			prg->lines.push_back(new_line);
		}
		src_line_nr++;
	}
}
bool t_compiler::compile(t_program* prg, t_program_line* new_line, string src_line, int src_line_nr) {
	int line_ix = prg->lines.size();
	src_line = String::Trim(src_line);
	if (is_comment(src_line)) {
		return false;
	}
	if (is_label(src_line)) {
		prg->labels[String::RemoveLast(src_line)] = line_ix;
		return false;
	}
	new_line->src = src_line;
	new_line->src_line_nr = src_line_nr;
	auto ixSpace = String::FindFirst(src_line, ' ');
	new_line->cmd = ixSpace >= 0 ? String::Trim(src_line.substr(0, ixSpace)) : src_line;
	new_line->cmd = String::ToUpper(new_line->cmd);
	auto raw_args = ixSpace >= 0 ? String::Trim(src_line.substr(ixSpace)) : "";
	std::vector<string> args;
	bool quote = false;
	string arg;

	for (int i = 0; i < raw_args.length(); i++) {
		char ch = raw_args[i];
		if (ch == '\"') {
			quote = !quote;
			arg += ch;
			if (!quote && i == raw_args.length() - 1) {
				args.push_back(String::Trim(arg));
				arg = "";
			}
		} else if (!quote && ch == ',' || i == raw_args.length() - 1) {
			if (ch != ',') arg += ch;
			args.push_back(String::Trim(arg));
			arg = "";
		} else {
			arg += ch;
		}
	}

	for (auto& arg : args) {
		t_param param;
		if (String::StartsWithNumber(arg) || String::StartsWith(arg, '-')) {
			param.type = t_param_type::number;
			param.number_literal = String::ToInt(arg);
		} else if (String::StartsAndEndsWith(arg, '"')) {
			param.type = t_param_type::string;
			param.string_literal = String::RemoveFirstAndLast(arg);
		} else if (String::StartsWith(arg, '$')) {
			if (String::Contains(arg, '[') && String::Contains(arg, ']')) {
				int ixOpenBracket = String::FindFirst(arg, '[') + 1;
				int ixCloseBracket = String::FindFirst(arg, ']');
				string index = String::Substring(arg, ixOpenBracket, ixCloseBracket);
				if (String::StartsWithNumber(index)) {
					param.type = t_param_type::array_index_literal;
					param.array_index_literal = String::ToInt(index);
				} else if (String::StartsWith(index, '$')) {
					param.type = t_param_type::array_index_variable;
					param.variable = String::Substring(arg, 1, ixOpenBracket - 1);
					param.array_index_variable = String::RemoveFirst(index);
				} else {
					add_error(src_line_nr, src_line, "Syntax error");
				}
			} else {
				param.type = t_param_type::variable;
				param.variable = String::RemoveFirst(arg);
			}
		} else if (String::StartsWithLetter(arg)) {
			param.type = t_param_type::label;
			param.label = arg;
		} else {
			add_error(src_line_nr, src_line, "Syntax error");
		}
		param.src = arg;
		new_line->params.push_back(param);
	}

	return true;
}
bool t_compiler::is_comment(string src) {
	return String::StartsWith(src, TOKEN_COMMENT);
}
bool t_compiler::is_label(string src) {
	return String::EndsWith(src, TOKEN_LABEL);
}
void t_compiler::add_error(int line, string src, string msg) {
	errors.push_back(String::Format("At line %i:\n%s\n\n%s", 
		line, msg.c_str(), src.c_str()));
}
