#pragma once
#include "common.h"

struct t_config {
	string autoload;
	string autorun;
	void load();
	void check_for_autorunnable_file();
};
