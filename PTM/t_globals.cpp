#include "t_globals.h"
#include "t_config.h"

t_globals::t_globals() {
	cfg = new t_config();
	snd = new TSound();
	wnd = nullptr;
#ifdef PTM_SHOW_PERFMON
	perfmon = new t_performance_monitor();
#else
	perfmon = nullptr;
#endif
}
t_globals::~t_globals() {
	delete cfg;
	delete snd;
	delete wnd;
	if (perfmon) delete perfmon;
}
