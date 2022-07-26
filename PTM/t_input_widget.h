#pragma once
#include "common.h"

struct t_globals;

struct t_input_widget {
	t_input_widget(t_globals* g);
	string show();
private:
	TTileBuffer* buf;
};
