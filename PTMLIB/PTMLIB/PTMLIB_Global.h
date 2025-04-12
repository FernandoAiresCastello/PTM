#pragma once
#include <SDL.h>

#ifdef TGLEXPORTS
	#define PTMAPI __declspec(dllexport)
#else
	#define PTMAPI __declspec(dllimport)
#endif
