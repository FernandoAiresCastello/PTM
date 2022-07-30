#pragma once
#include "common.h"
#include "t_performance_monitor.h"

struct t_config;

struct t_globals {
	t_globals();
	~t_globals();
	t_config* cfg = nullptr;
	TBufferedWindow* wnd = nullptr;
	TSound* snd = nullptr;
	t_performance_monitor* perfmon = nullptr;
};
