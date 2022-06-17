#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	int fg_color = 0x0d;
	int bg_color = 0x90;
	int bdr_color = 0x92;
	void load();
};
