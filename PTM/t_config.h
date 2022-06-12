#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	int cols = 33;
	int rows = 25;
	int pixel_w = 4;
	int pixel_h = 3;
	int fg_color = 0x0d;
	int bg_color = 0x90;
	int bdr_color = 0x92;
	void load();
};
