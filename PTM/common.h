#pragma once
#include <SDL.h>
#include <CppUtils.h>
#include <TileGameLib.h>
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace CppUtils;
using namespace TileGameLib;
using string = std::string;

#define debugger __debugbreak()

#define PTM_CONFIG_FILE		"PTM.cfg"
#define PTM_DEBUG_FILE		"PTM.dbg"

#define PTM_INVALID_NUMBER	INT_MIN
