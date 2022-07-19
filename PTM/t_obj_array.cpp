#include "t_obj_array.h"

t_obj_array::t_obj_array() {
	width = 0;
	height = 0;
}
t_obj_array::t_obj_array(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < width * height; i++) {
		objs.push_back(t_obj());
	}
}
