#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	string programs_path;
	void load();
};
