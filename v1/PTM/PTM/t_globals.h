#pragma once
#include "common.h"
#include "t_performance_monitor.h"

struct t_globals {
	t_globals();
	~t_globals();
	TBufferedWindow* wnd = nullptr;
	TSound* snd = nullptr;
	t_performance_monitor* perfmon = nullptr;
};
