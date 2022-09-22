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
		bool must_add_line = compile_line(prg, &new_line, src_line, src_line_nr);
		if (must_add_line) {
			prg->lines.push_back(new_line);
		}
		src_line_nr++;
	}
}
bool t_compiler::compile_line(
	t_program* prg, t_program_line* new_line, string& src_line, int src_line_nr) {
	src_line = String::Trim(src_line);

	// Ignore comment line
	if (is_comment(src_line)) {
		return false;
	}
	// Parse label
	if (is_label(src_line)) {
		string label = String::Trim(String::RemoveLast(src_line));
		if (prg->labels.find(label) == prg->labels.end()) {
			prg->labels[label] = prg->lines.size();
		} else {
			add_error(src_line_nr, src_line, "Duplicated label");
		}
		return false;
	}
	// Check for invalid line start
	if (is_invalid_line_start(src_line)) {
		add_syntax_error(src_line_nr, src_line);
		return false;
	}
	// Store source line info
	new_line->src = src_line;
	new_line->src_line_nr = src_line_nr;

	// Parse command name
	auto ixSpace = String::FindFirst(src_line, ' ');
	new_line->cmd = ixSpace != string::npos ? String::Trim(src_line.substr(0, ixSpace)) : src_line;
	new_line->cmd = String::ToUpper(new_line->cmd);

	// Check for ENDIF
	if (is_endif(new_line->cmd)) {
		new_line->is_endif = true;
		return true;
	}

	// Parse raw command argument list
	auto raw_args = ixSpace != string::npos ? String::Trim(src_line.substr(ixSpace)) : "";
	auto args = parse_args(raw_args);
	// Compile command arguments info
	for (auto& arg : args) {
		t_param param;

		if (is_number(arg)) { // Number
			param.type = t_param_type::number;
			param.numeric_value = String::ToInt(arg);
			param.textual_value = arg;

		} else if (is_string_literal(arg)) { // String literal
			param.type = t_param_type::string;
			param.textual_value = String::RemoveFirstAndLast(arg);
			param.numeric_value = String::ToInt(param.textual_value);

		} else if (is_char_literal(arg)) { // Character literal
			param.type = t_param_type::char_literal;
			string raw = String::RemoveFirstAndLast(arg);
			if (raw.length() != 1) {
				add_syntax_error(src_line_nr, src_line);
			} else {
				param.textual_value = raw;
				param.numeric_value = raw[0];
			}

		} else if (is_array_identifier(arg)) { // Array identifier
			auto begin = String::IndexOf(arg, '[');
			auto end = String::IndexOf(arg, ']');
			if (begin == string::npos || end == string::npos || begin >= end) {
				add_syntax_error(src_line_nr, src_line);
			} else {
				param.id = String::Substring(arg, 0, begin);
				string ix = String::Substring(arg, begin + 1, end);

				if (String::StartsWithNumber(ix)) { // Literal array index
					param.type = t_param_type::arr_ix_literal;
					param.arr_ix_literal = String::ToInt(ix);

				} else if (String::StartsWithLetter(ix)) { // Variable array index
					param.type = t_param_type::arr_ix_var;
					param.arr_ix_var = ix;
				} else {
					add_syntax_error(src_line_nr, src_line);
				}
			}

		} else if (is_variable_identifier(arg)) { // Variable identifier
			param.type = t_param_type::id;
			param.id = arg;
		} else {
			add_syntax_error(src_line_nr, src_line);
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
void t_compiler::add_syntax_error(int src_line_nr, string src) {
	add_error(src_line_nr, src, "Syntax error");
}
bool t_compiler::is_invalid_line_start(string& src_line) {
	return !src_line.empty() && !String::StartsWithLetter(src_line);
}
bool t_compiler::has_leading_whitespace(string& src_line) {
	return String::StartsWith(src_line, ' ');
}
bool t_compiler::is_comment(string& src_line) {
	return String::StartsWith(src_line, ';');
}
bool t_compiler::is_label(string& src_line) {
	return String::EndsWith(src_line, ":");
}
std::vector<string> t_compiler::parse_args(string& raw_args) {
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
	return args;
}
bool t_compiler::is_number(string& arg) {
	return
		String::StartsWithNumber(arg) ||
		String::StartsWith(arg, '-') ||
		String::StartsWith(arg, '+');
}
bool t_compiler::is_string_literal(string& arg) {
	return String::StartsAndEndsWith(arg, '"');
}
bool t_compiler::is_char_literal(string& arg) {
	return String::StartsAndEndsWith(arg, '\'');
}
bool t_compiler::is_variable_identifier(string& arg) {
	bool has_invalid_chars =
		String::Contains(arg, ';');

	if (has_invalid_chars) return false;

	bool is_valid =
		String::StartsWith(arg, '$') ||
		String::StartsWithLetter(arg);

	return is_valid;
}
bool t_compiler::is_array_identifier(string& arg) {
	return 
		String::Contains(arg, '[') || 
		String::Contains(arg, ']');
}
bool t_compiler::is_endif(string& arg) {
	return arg == "ENDIF";
}
