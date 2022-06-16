#pragma once
#include "common.h"

struct t_config;

struct t_globals {
	t_globals();
	~t_globals();
	t_config* cfg = nullptr;
	TBufferedWindow* wnd = nullptr;
	TSound* snd = nullptr;
};
