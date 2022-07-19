#pragma once
#include "common.h"
#include "t_obj.h"

struct t_obj_array {
	int width;
	int height;
	std::vector<t_obj> objs;
	t_obj_array();
	t_obj_array(int w, int h);
};
