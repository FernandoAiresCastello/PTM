#include "t_globals.h"
#include "t_config.h"

t_globals::t_globals() {
	cfg = new t_config();
	snd = new TSound();
	wnd = nullptr;
}
t_globals::~t_globals() {
	delete cfg;
	delete snd;
	delete wnd;
}
