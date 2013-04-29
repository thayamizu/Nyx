#pragma once

//標準ライブラリ
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <deque>
#include <map>
#include <set>

//テスティングフレームワーク(WinUnit)
#include <WinUnit.h>
#include <WinUnitLogger.h>
#pragma comment(lib, "WinUnitLib.lib")

//対象ライブラリ
#include "../../Nyx/Source/NyxCore.h"
#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../../Lib/Release/Nyx_MT.lib")
#endif

