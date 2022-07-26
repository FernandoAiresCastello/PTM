#include "t_config.h"

#define CONFIG_FILE "config.ini"

void t_config::load() {
	if (!File::Exists(CONFIG_FILE)) return;
	for (auto& rawline : File::ReadLines(CONFIG_FILE, "\r\n")) {
		string line = String::Trim(rawline);
		if (line.empty() || String::StartsWith(line, '#')) continue;
		auto cfg = String::Split(line, '=', true);
		if (cfg.size() != 2) continue;
		string name = cfg[0];
		string value = cfg[1];
		
		if (name == "autoload") {
			autoload = value;
		} else if (name == "autorun") {
			autorun = value;
		}
	}
}
void t_config::check_for_autorunnable_file() {
	if (File::Exists("exec")) {
		autorun = "exec";
		return;
	}
	/*
	string exe_path = __argv[0];
	int ix_last_slash = String::FindLast(exe_path, '\\');
	string exe_file;
	if (ix_last_slash > 0) {
		exe_file = String::Skip(exe_path, ix_last_slash + 1);
	} else {
		exe_file = exe_path;
	}
	string exe_name;
	if (String::EndsWith(exe_file, ".exe")) {
		exe_name = String::Substring(exe_file, 0, exe_file.length() - 4);
	} else {
		exe_name = exe_file;
	}
	string autorunnable_file = exe_name + ".dat";
	if (File::Exists(autorunnable_file)) {
		autorun = autorunnable_file;
	}
	*/
}
