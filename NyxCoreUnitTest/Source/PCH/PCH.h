#ifndef NYX_CORE_UNIT_TEST_PCH_H_
#define NYX_CORE_UNIT_TEST_PCH_H_
#include <TCHAR.h>
#include <Windows.h>
#include <WinUnit.h>
#include <WinUnitLogger.h>
#pragma comment(lib, "WinUnitLib.lib")


#include "../../Nyx/Source/NyxCore.h"
#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../../Lib/Release/Nyx_MT.lib")
#endif

#endif