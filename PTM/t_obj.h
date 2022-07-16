#pragma once
#include "common.h"

struct t_obj {
	TTileSeq tile;
	CppProperties prop;
	t_obj& operator=(const t_obj& other);
};
