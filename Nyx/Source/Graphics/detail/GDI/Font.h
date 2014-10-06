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
#ifndef NYX_CORE_INCLUDED_FONT_H_
#define NYX_CORE_INCLUDED_FONT_H_

namespace nyx {
	namespace win32 {

		typedef HFONT font_handle;

		/// フォント
		class font {
		public:
			//------------------------------------------------------------------------------
			//構築・破壊
			//------------------------------------------------------------------------------
			/**
			*
			*/
			font(const int height_, const int angle_, const std::wstring face_);
			/**
			*
			*/
			font(const int height_, const int angle_, const int weight_, const bool isItalic_, const bool isUnderLine_, const bool isStrike_, const int charset_, const std::wstring face_);
			/**
			*
			*/
			font(const font& font_);

			/**
			*
			*/
			~font();

			//------------------------------------------------------------------------------
			//フォントのセット
			//------------------------------------------------------------------------------
			/**
			*
			*/
			void set(const int h, const int angle, const std::wstring face);
			/**
			*
			*/
			void set(const int height_, const int angle_, const int weight_, const bool isItalic_, const bool isUnderLine_, const bool isStrike_, const int charset_, const std::wstring face);


			//------------------------------------------------------------------------------
			//描画
			//------------------------------------------------------------------------------
			/**
			*
			*/
			void draw(HDC hdc, const wchar_t* text_, RECT rect_);
			/**
			*
			*/
			void draw(HDC hdc, const std::wstring text_, RECT rect_);

			//------------------------------------------------------------------------------
			//取得
			//------------------------------------------------------------------------------
			/**
			*
			*/
			int get_angle();
			/**
			*
			*/
			int get_height();
			/**
			*

			*/int get_font_weight();
			/**
			*
			*/
			bool is_italic();
			/**
			*
			*/
			bool is_underline();
			/**
			*
			*/
			font_handle get_font_handle();
		private:
			font(); 
			int angle_; 
			int height_;
			int weight_;
			int charset_;
			bool isItalic_;
			bool isStrike_;
			bool isUnderLine_;
			std::wstring fontFace_;
			font_handle fontHandle_;
		};
	}
}
#endif