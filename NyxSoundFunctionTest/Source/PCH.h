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


//対象ライブラリ
#include <NyxCore.h>
#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../../Lib/Release/Nyx_MT.lib")
#endif


const std::wstring g_waveFile = L"..\\..\\TestData\\Sound\\test.wav";