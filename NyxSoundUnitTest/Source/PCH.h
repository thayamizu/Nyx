#pragma once

//�W�����C�u����
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

//�e�X�e�B���O�t���[�����[�N(WinUnit)
#include <WinUnit.h>
#include <WinUnitLogger.h>
#pragma comment(lib, "WinUnitLib.lib")

//�Ώۃ��C�u����
#include "../../Nyx/Source/NyxCore.h"
#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../../Lib/Release/Nyx_MT.lib")
#endif

