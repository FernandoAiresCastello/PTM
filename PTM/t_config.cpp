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
