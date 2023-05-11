#pragma once
#include <SDL.h>
#include <CppUtils.h>
#include <TileGameLib.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

using namespace CppUtils;
using namespace TileGameLib;
using string = std::string;

#define debugger __debugbreak()

#define PTM_SHOW_PERFMON

#define PTM_CONFIG_FILE		"PTM.cfg"
#define PTM_DEBUG_FILE		"PTM.dbg"
#define PTM_LAST_FILE		"PTM.last"
#define PTM_MAIN_PROG_FILE	"main.ptm"
#define PTM_SCRSHOT_FILE	"PTM.bmp"

#define PTM_INVALID_NUMBER	INT_MIN
