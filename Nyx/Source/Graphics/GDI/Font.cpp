/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Utility/Common.h"
#include "Debug/Assert.h"
#include "Graphics/GDI/Font.h"

namespace Nyx {
	namespace GDI {

		//------------------------------------------------------------------------------
		//
		Font::Font(const int height_, const int angle_, const std::wstring face_) {
			Set(height_, angle_, face_);   


		}

		//------------------------------------------------------------------------------
		//
		Font::Font(const int height_, const int angle_, const int weight_, 
			const bool isItalic_, const bool isUnderLine_, const bool isStrike_, 
			const int charset_, const std::wstring face_) 
		{
			Set(height_, angle_, weight_, isItalic_, isUnderLine_,isStrike_, charset_ ,face_);
		}

		//------------------------------------------------------------------------------
		//
		Font::Font(const Font &font_) {
			height = font_.height;                     
			angle  = font_.angle;                 
			weight = font_.weight;FW_REGULAR;             
			isItalic   = font_.isItalic;                    
			isUnderLine= font_.isUnderLine;                  
			isStrike   = font_.isStrike;                 
			charset = font_.charset;      
			face    = font_.face.c_str();           



		}

		//------------------------------------------------------------------------------
		//
		Font::~Font() {

		}

		//------------------------------------------------------------------------------
		//
		void Font::Set(const int height_,const int angle_, const std::wstring face_) {
			height = height_;                      //文字幅（高さと同じ）
			angle  = angle_;                  //テキストの角度
			weight = FW_REGULAR;             //フォントの重さ（太さ）
			isItalic    = false;
			isUnderLine = false;                  //アンダーライン
			isStrike   = false;                  //打ち消し線
			charset = SHIFTJIS_CHARSET;       //文字セット
			face    = face_;                  //書体名

			font=  CreateFont(
				height,       //フォント高さ
				0,                      //文字幅（高さと同じ）
				angle,                  //テキストの角度
				0,                      //ベースラインとｘ軸との角度
				weight,             //フォントの重さ（太さ）
				isItalic,                  //イタリック体
				isUnderLine,                  //アンダーライン
				isStrike,                  //打ち消し線
				charset,       //文字セット
				OUT_TT_ONLY_PRECIS,     //出力精度
				CLIP_DEFAULT_PRECIS,    //クリッピング精度
				PROOF_QUALITY,          //出力品質
				FIXED_PITCH|FF_MODERN,  //ピッチとファミリー
				face.c_str());                  //書体名

			Assert(font != NULL);
		}

		//------------------------------------------------------------------------------
		//
		void Font::Set(const int height_, const int angle_, const int weight_,
			const bool isItalic_, const bool isUnderLine_, const bool isStrike_, 
			const int charset_, const std::wstring face_) {
				height = height_;                      //文字幅（高さと同じ）
				angle  = angle_;                  //テキストの角度
				weight = weight_;             //フォントの重さ（太さ）
				isItalic    = isItalic_;
				isUnderLine = isUnderLine_;                  //アンダーライン
				isStrike    = isStrike_;                  //打ち消し線
				charset = charset_;       //文字セット
				face    = face_;                  //書体名

				font=  CreateFont(
					height,       //フォント高さ
					0,                      //文字幅（高さと同じ）
					angle,                  //テキストの角度
					0,                      //ベースラインとｘ軸との角度
					weight,             //フォントの重さ（太さ）
					isItalic,                  //イタリック体
					isUnderLine,                  //アンダーライン
					isStrike,                  //打ち消し線
					charset,       //文字セット
					OUT_TT_ONLY_PRECIS,     //出力精度
					CLIP_DEFAULT_PRECIS,    //クリッピング精度
					PROOF_QUALITY,          //出力品質
					FIXED_PITCH|FF_MODERN,  //ピッチとファミリー
					face.c_str());                  //書体名

				Assert(font != NULL);
		} 

		//------------------------------------------------------------------------------
		//
		void Font::Draw(HDC hdc, const wchar_t* text_, RECT rect) {
			SelectObject(hdc, font);
			DrawText(hdc, text_, -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		void Font::Draw(HDC hdc, const std::wstring text_,RECT rect) {
			SelectObject(hdc, font);
			DrawText(hdc, text_.c_str(), -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		int Font::GetAngle() {
			return angle;
		}

		//------------------------------------------------------------------------------
		//
		int Font::GetHeight() {
			return height;
		}

		//------------------------------------------------------------------------------
		//  
		int Font::GetWeight() {
			return weight;
		}

		//------------------------------------------------------------------------------
		//  
		bool Font::IsItalic() {
			return isItalic;
		}

		//------------------------------------------------------------------------------
		//
		bool Font::IsUnderLine() {
			return isUnderLine;
		}

		//------------------------------------------------------------------------------
		//            
		HFONT Font::GetFont() {
			return font;    
		}
	}
}