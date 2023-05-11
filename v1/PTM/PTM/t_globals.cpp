#include "t_globals.h"

t_globals::t_globals() {
	snd = new TSound();
	wnd = nullptr;
#ifdef PTM_SHOW_PERFMON
	perfmon = new t_performance_monitor();
#else
	perfmon = nullptr;
#endif
}
t_globals::~t_globals() {
	delete snd;
	delete wnd;
	if (perfmon) delete perfmon;
}
