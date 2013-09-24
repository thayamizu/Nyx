/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_PCH_H_ 
#define NYX_CORE_INCLUDED_PCH_H_


//Windows
#ifdef _WIN32

//header
#include <windows.h>
#include <mmsystem.h>

//Windows Library
#pragma comment( lib, "msimg32.lib" )
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )
#pragma comment( lib, "winmm.lib" )

#endif

//�C�����C���֐��̐[��
#pragma inline_depth ( 16 )
#pragma inline_recursion ( on )

#pragma warning(disable:4201)

//STL 
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <sstream>

//Common
#include "Utility/Common.h"
#include "Utility/Exception.h"
#include "Utility/Type.h"
#include "Utility/Limits.h"
#include "Utility/Math.h"
#include "Utility/Random.h"

//DirectX
#include "Graphics/DirectXDefinition.h"

#endif