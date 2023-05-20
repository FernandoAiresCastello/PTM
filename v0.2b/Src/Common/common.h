#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

#include "../CppUtils/CppUtils.h"
using namespace CppUtils;

#define debugger			__debugbreak()
#define PTM_INVALID_NUMBER	INT_MIN
#define PTM_MSGBOX_TITLE	"PTM"

typedef unsigned int	rgb;
typedef unsigned char	byte;
typedef size_t			addr;
typedef string			binary;
