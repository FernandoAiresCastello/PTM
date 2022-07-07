#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	int csr_fg_color = 7;
	int fg_color = 1;
	int bg_color = 2;
	int bdr_fg_color = 3;
	int bdr_bg_color = 4;
	int label_fg_color = 5;
	int cmd_fg_color = 6;
	void load();
};
