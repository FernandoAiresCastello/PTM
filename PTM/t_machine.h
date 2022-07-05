#pragma once
#include "common.h"

struct t_machine {
	TBufferedWindow* wnd;
	
	t_machine(TBufferedWindow* wnd);
	~t_machine();
};
