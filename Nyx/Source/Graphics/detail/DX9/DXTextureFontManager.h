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
#ifndef NYX_CORE_INCLUDED_DIRECT_GRAPHICS_TEXTURE_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_DIRECT_GRAPHICS_TEXTURE_FONT_MANAGER_H_

namespace Nyx {
	namespace DX9 {
		///文字一つ描画するときに必要な情報
		struct CharInfo {
			bool isDrawed;///<描画されている
			uchar transparency;///< 透明度(0~255)
		};

		//前方宣言
		///テクスチャフォントの管理クラス
		class DXTextureFontManager {
			typedef std::vector<CharInfo> CharInfoContainer;
			typedef std::vector<DXTextureFont*> DXTextureFontContainer;
		public:
			//--------------------------------------------------------------------------------------
			// 構築・破壊
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			DXTextureFontManager();

			/**
			*
			*/
			DXTextureFontManager(int capacity, std::wstring font, int size, Color4c color, int speed);

			/**
			*
			*/
			~DXTextureFontManager();

			//--------------------------------------------------------------------------------------
			// テクスチャのロード・解放
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			int Load(DirectGraphicsDevice&);

			/**
			*
			*/
			void Release();

			/**
			*
			*/
			bool OnResetDevice();

			/**
			*
			*/
			bool OnLostDevice();

			//--------------------------------------------------------------------------------------
			// 描画
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			void RenderAll(float x, float y, float z,  float sx=1, float sy=1, float angle=0);

			/**
			*
			*/
			void Render(int index, float x, float y, float z,  float sx=1, float sy=1, float angle=0);

			//--------------------------------------------------------------------------------------
			// 文字列の設定
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			void SetText(std::wstring text);

			/**
			*
			*/
			std::wstring GetText() const;

			/**
			*
			*/
			void SetTextLength(int len);

			/**
			*
			*/
			int GetTextLength() const;

			//--------------------------------------------------------------------------------------
			// フォント情報の取得・設定
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			void AdjustRowAndColumn(int width, int height);
			/**
			*
			*/
			void SetFontSize(int size);
			/**
			*
			*/
			int GetFontSize() const;

			/**
			*
			*/
			void SetFontColor(Color4c color);

			/**
			*
			*/
			Color4c GetFontColor()const;

			/**
			*
			*/
			void SetRow(int n);
			/**
			*
			*/
			int GetRow() const;

			/**
			*
			*/
			void SetColumn(int n);

			/**
			*
			*/
			int GetColumn() const;

			/**
			*
			*/
			void SetSpeed(int s);
			/**
			*
			*/
			int GetSpeed() const;


			/**
			*
			*/
			void SetTransparent(int s);
			/**
			*
			*/
			int GetTransparent() const;
		private:
			static const int defaultTransparent;

		private:

			Color4c fontColor;///<フォントカラー
			int transparent;///< 透過率
			int fontSize;///< フォントサイズ
			int textSpeed;///< 文字送りの速さ
			size_t textLength;///< 一度に描画するテキストの長さ
			int rowNum;   ///< １行で表示する文字数
			int columnNum;///< 1列に表示する文字数
			uint cursorRead;///< すでに作成したものまでの;
			std::wstring fontName;///使用するフォントの名前
			std::wstring textstring;///<ロードしている文字列
			CharInfoContainer charInfo;
			DXTextureFontContainer container;///< 個々の文字テクスチャを格納してるコンテナ
		};
	}
}
#endif