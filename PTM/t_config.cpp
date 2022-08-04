#include "t_config.h"

void t_config::load() {
	if (File::Exists(PTM_CONFIG_FILE)) {
		for (auto& rawline : File::ReadLines(PTM_CONFIG_FILE, "\r\n")) {
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
			} else if (name == "programs_path") {
				programs_path = value;
			}
		}
	} else {
		string exe_name = File::GetCurrentExecutableFileName(true);
		string autorunnable_file = exe_name + ".ptm";
		if (File::Exists(autorunnable_file)) {
			autorun = autorunnable_file;
		}
	}
}
