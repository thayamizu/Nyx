#ifndef NYX_CORE_INCLUDED_FONT_INFO_H_
#define NYX_CORE_INCLUDED_FONT_INFO_H_
#include "Primitive/Color4.h"

namespace nyx {

	///�t�H���g���
	struct font_info
	{
		int			   fontSize;///�t�H���g�T�C�Y
		std::wstring   fontFace;///�t�H���g�t�F�C�X
		color4c fontColor;///�t�H���g�J���[
	};
}
#endif