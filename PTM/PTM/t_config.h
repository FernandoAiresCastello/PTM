#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	int cols = 33;
	int rows = 25;
	int pixel_w = 3;
	int pixel_h = 3;
	void load();
};
