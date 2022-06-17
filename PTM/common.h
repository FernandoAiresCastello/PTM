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
using ixp = PaletteIndex;
using ixc = CharsetIndex;

#define debugger __debugbreak()
#define ILLEGAL_ADDRESS -1
#define MEMORY_TOP 0x10000
