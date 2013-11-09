#ifndef NYX_CORE_INCLUDED_FONT_INFO_H_
#define NYX_CORE_INCLUDED_FONT_INFO_H_
#include "Primitive/Color4.h"

namespace Nyx {

	///フォント情報
	struct FontInfo
	{
		int			   fontSize;///フォントサイズ
		std::wstring   fontFace;///フォントフェイス
		Color4c fontColor;///フォントカラー
	};
}
#endif