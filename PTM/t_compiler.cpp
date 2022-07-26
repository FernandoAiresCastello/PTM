#include "t_compiler.h"
#include "t_program.h"
#include "t_program_line.h"

void t_compiler::run(t_program* prg) {
	errors.clear();
	prg->lines.clear();
	prg->labels.clear();
	int src_line_nr = 1;
	for (auto& src_line : prg->src_lines) {
		t_program_line new_line;
		bool must_add_line = compile(prg, &new_line, src_line, src_line_nr);
		if (must_add_line) {
			prg->lines.push_back(new_line);
		}
		src_line_nr++;
	}
}
bool t_compiler::compile(t_program* prg, t_program_line* new_line, string src_line, int src_line_nr) {
	if (String::StartsWith(src_line, ' ')) {
		add_error(src_line_nr, src_line, "Leading whitespace is not allowed");
		return false;
	}
	src_line = String::Trim(src_line);
	if (String::StartsWith(src_line, ';')) {
		return false;
	}
	if (String::StartsWith(src_line, ":")) {
		string label = String::Trim(String::Skip(src_line, 1));
		prg->labels[label] = prg->lines.size();
		return false;
	}
	if (!src_line.empty() && !String::StartsWithLetter(src_line)) {
		add_error(src_line_nr, src_line, "Syntax error");
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
		if (String::StartsWithNumber(arg) || String::StartsWith(arg, '-') || String::StartsWith(arg, '+')) {
			// Number
			param.type = t_param_type::number;
			param.numeric_value = String::ToInt(arg);
			param.textual_value = arg;
		} else if (String::StartsAndEndsWith(arg, '"')) {
			// String literal
			param.type = t_param_type::string;
			param.textual_value = String::RemoveFirstAndLast(arg);
			param.numeric_value = String::ToInt(param.textual_value);
		} else if (String::StartsAndEndsWith(arg, '\'')) {
			// Character literal
			param.type = t_param_type::char_literal;
			string raw = String::RemoveFirstAndLast(arg);
			if (raw.length() != 1) {
				add_error(src_line_nr, src_line, "Syntax error");
			} else {
				param.textual_value = raw;
				param.numeric_value = raw[0];
			}
		} else if (String::StartsWithLetter(arg)) {
			// Identifier
			if (String::Contains(arg, '[') && !String::Contains(arg, ']') ||
				String::Contains(arg, ']') && !String::Contains(arg, '[')) {
				add_error(src_line_nr, src_line, "Syntax error");
			} else if (String::Contains(arg, '[') && String::Contains(arg, ']')) {
				// Array identifier
				int begin = String::FindFirst(arg, '[');
				int end = String::FindLast(arg, ']');
				if (begin >= end) {
					add_error(src_line_nr, src_line, "Syntax error");
				} else {
					param.id = String::Substring(arg, 0, begin);
					string ix = String::Substring(arg, begin + 1, end);
					if (String::StartsWithNumber(ix) || String::StartsWith(ix, '-') || String::StartsWith(ix, '+')) {
						// Literal array index
						param.type = t_param_type::arr_ix_literal;
						param.arr_ix_literal = String::ToInt(ix);
					} else if (String::StartsWithLetter(ix)) {
						// Variable array index
						param.type = t_param_type::arr_ix_var;
						param.arr_ix_var = ix;
					} else {
						add_error(src_line_nr, src_line, "Syntax error");
					}
				}
			} else {
				// Variable identifier
				param.type = t_param_type::id;
				param.id = arg;
			}
		} else {
			add_error(src_line_nr, src_line, "Syntax error");
		}
		param.src = arg;
		new_line->params.push_back(param);
	}

	return true;
}
void t_compiler::add_error(int line, string src, string msg) {
	errors.push_back(String::Format("COMPILE ERROR\nAt line %i:\n%s\n\n%s", 
		line, msg.c_str(), src.c_str()));
}
