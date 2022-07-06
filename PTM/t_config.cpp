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
		} else if (name == "color") {
			auto values = String::Split(value, ' ', true);
			if (values.size() != 4) continue;
			fg_color = String::ToInt(values[0]);
			bg_color = String::ToInt(values[1]);
			bdr_fg_color = String::ToInt(values[2]);
			bdr_bg_color = String::ToInt(values[3]);
		}
	}
}
