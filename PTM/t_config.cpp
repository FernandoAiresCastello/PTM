#include "t_config.h"

void t_config::load() {
	if (!File::Exists("boot.cfg")) return;
	for (auto& rawline : File::ReadLines("boot.cfg", "\r\n")) {
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
