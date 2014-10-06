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
#include "Graphics/detail/GDI/Font.h"

namespace nyx {
	namespace win32 {

		//------------------------------------------------------------------------------
		//
		font::font(const int height_, const int angle_, const std::wstring face_) 
		:fontHandle_(NULL){
			set(height_, angle_, face_);   


		}

		//------------------------------------------------------------------------------
		//
		font::font(const int height_, const int angle_, const int weight_,
			const bool isItalic_, const bool isUnderLine_, const bool isStrike_,
			const int charset_, const std::wstring face_)
			:fontHandle_(NULL)
		{
			set(height_, angle_, weight_, isItalic_, isUnderLine_,isStrike_, charset_ ,face_);
		}

		//------------------------------------------------------------------------------
		//
		font::font(const font &font_) {
			height_ = font_.height_;                     
			angle_  = font_.angle_;                 
			weight_ = font_.weight_;FW_REGULAR;             
			isItalic_   = font_.isItalic_;                    
			isUnderLine_= font_.isUnderLine_;                  
			isStrike_   = font_.isStrike_;                 
			charset_ = font_.charset_;      
			fontFace_    = font_.fontFace_.c_str();           



		}

		//------------------------------------------------------------------------------
		//
		font::~font() {

		}

		//------------------------------------------------------------------------------
		//
		void font::set(const int height,const int angle, const std::wstring face) {
			height_ = height;                      //文字幅（高さと同じ）
			angle_  = angle;                  //テキストの角度
			weight_ = FW_REGULAR;             //フォントの重さ（太さ）
			isItalic_    = false;
			isUnderLine_ = false;                  //アンダーライン
			isStrike_   = false;                  //打ち消し線
			charset_ = SHIFTJIS_CHARSET;       //文字セット
			fontFace_    = face;                  //書体名

			fontHandle_=  CreateFont(
				height_,       //フォント高さ
				0,                      //文字幅（高さと同じ）
				angle_,                  //テキストの角度
				0,                      //ベースラインとｘ軸との角度
				weight_,             //フォントの重さ（太さ）
				isItalic_,                  //イタリック体
				isUnderLine_,                  //アンダーライン
				isStrike_,                  //打ち消し線
				charset_,       //文字セット
				OUT_TT_ONLY_PRECIS,     //出力精度
				CLIP_DEFAULT_PRECIS,    //クリッピング精度
				PROOF_QUALITY,          //出力品質
				FIXED_PITCH|FF_MODERN,  //ピッチとファミリー
				fontFace_.c_str());                  //書体名

			NYX_ASSERT(fontHandle_ != NULL);
		}

		//------------------------------------------------------------------------------
		//
		void font::set(const int height, const int angle, const int weight,
			const bool isItalic, const bool isUnderLine, const bool isStrike, 
			const int charset, const std::wstring face) {
				height_ = height;                      //文字幅（高さと同じ）
				angle_  = angle;                  //テキストの角度
				weight_ = weight;             //フォントの重さ（太さ）
				isItalic_    = isItalic;
				isUnderLine_ = isUnderLine;                  //アンダーライン
				isStrike_    = isStrike;                  //打ち消し線
				charset_ = charset;       //文字セット
				fontFace_    = face;                  //書体名

				fontHandle_=  CreateFont(
					height_,       //フォント高さ
					0,                      //文字幅（高さと同じ）
					angle_,                  //テキストの角度
					0,                      //ベースラインとｘ軸との角度
					weight_,             //フォントの重さ（太さ）
					isItalic_,                  //イタリック体
					isUnderLine_,                  //アンダーライン
					isStrike_,                  //打ち消し線
					charset_,       //文字セット
					OUT_TT_ONLY_PRECIS,     //出力精度
					CLIP_DEFAULT_PRECIS,    //クリッピング精度
					PROOF_QUALITY,          //出力品質
					FIXED_PITCH|FF_MODERN,  //ピッチとファミリー
					fontFace_.c_str());                  //書体名

				NYX_ASSERT(fontHandle_ != NULL);
		} 

		//------------------------------------------------------------------------------
		//
		void font::draw(HDC hdc, const wchar_t* text_, RECT rect) {
			SelectObject(hdc, fontHandle_);
			DrawText(hdc, text_, -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		void font::draw(HDC hdc, const std::wstring text_,RECT rect) {
			SelectObject(hdc, fontHandle_);
			DrawText(hdc, text_.c_str(), -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		int font::get_angle() {
			return angle_;
		}

		//------------------------------------------------------------------------------
		//
		int font::get_height() {
			return height_;
		}

		//------------------------------------------------------------------------------
		//  
		int font::get_font_weight() {
			return weight_;
		}

		//------------------------------------------------------------------------------
		//  
		bool font::is_italic() {
			return isItalic_;
		}

		//------------------------------------------------------------------------------
		//
		bool font::is_underline() {
			return isUnderLine_;
		}

		//------------------------------------------------------------------------------
		//            
		font_handle font::get_font_handle() {
			return fontHandle_;    
		}
	}
}