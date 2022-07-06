#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	int fg_color = 0x0c;
	int bg_color = 0x80;
	int bdr_fg_color = 0x08;
	int bdr_bg_color = 0x82;
	void load();
};
