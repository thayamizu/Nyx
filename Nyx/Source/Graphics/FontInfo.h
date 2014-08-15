#ifndef NYX_CORE_INCLUDED_FONT_INFO_H_
#define NYX_CORE_INCLUDED_FONT_INFO_H_
#include "Primitive/Color4.h"

namespace nyx {

	///フォント情報
	struct font_info
	{
		int			   fontSize;///フォントサイズ
		std::wstring   fontFace;///フォントフェイス
		color4c fontColor;///フォントカラー
	};
}
#endif