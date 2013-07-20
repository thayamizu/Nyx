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
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/ITextureFont.h"
#include "Graphics/DX9/DXTextureFont.h"
#include "Graphics/DX9/DXTextureFontManager.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Color4.h"
#include "Thread/Thread.h"
namespace Nyx {
	namespace DX9 {

		//-----------------------------------------------------------------------------------------
		//
		const int DXTextureFontManager::defaultTransparent = 255;

		//-----------------------------------------------------------------------------------------
		//
		DXTextureFontManager::DXTextureFontManager() 
			:fontSize(32), fontName(L"ＭＳ 明朝"),fontColor(Color4c::White), textSpeed(10),rowNum(12), columnNum(3),cursorRead(0),
			transparent(defaultTransparent)
		{
			textstring.reserve(255);
			container.reserve(255);
			charInfo.reserve(255);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXTextureFontManager::DXTextureFontManager(int capacity, std::wstring font, int size,Color4c color, int speed)
			:fontName(font),fontSize(size), fontColor(color), textSpeed(speed),rowNum(12), columnNum(3),cursorRead(0),
			transparent(defaultTransparent)
		{
			textstring.reserve(capacity);
			container.reserve(capacity);
			charInfo.reserve(capacity);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXTextureFontManager::~DXTextureFontManager()
		{

			Release();
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::Load(DirectGraphicsDevice& device)
		{
			Release();	
			CharInfo info={false, 0};
			//セットしている文字列からフォントを作成
			uint n = textLength;//rowNum*columnNum; //読み込む文字数
			uint pos;
			for (pos=0; pos < n; pos++) {
				if ((cursorRead + pos) >= textstring.size()) {break;}
				DXTextureFont * font = new DXTextureFont();
				Assert(font != NULL);
				font->Create(device, fontSize, &textstring[cursorRead + pos], fontName);


				charInfo.push_back(info);
				container.push_back(font);

			}
			//最初の文字を描画済みに設定
			if (pos != 0) {
				charInfo[0].isDrawed = true;
				charInfo[0].transparency = 255;
			}

			//読み込んだ位置を記憶
			cursorRead += pos;

			//ロードした要素を返す
			return pos;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::Release() {
			int size= container.size();
			for (int i=0; i < size; ++i) {
				if (container[i] != NULL ) {
					SafeDelete(container[i]);
				}
			}

			container.clear();
			charInfo.clear();
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXTextureFontManager::OnResetDevice() {
			int size = container.size();
			for (int i=0; i<size; i++) {
				HRESULT hr = container[i]->OnResetDevice();
				if (FAILED(hr)) {
					return false;
				}
			}
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//
		bool DXTextureFontManager::OnLostDevice() {
			int size = container.size();
			for (int i=0; i<size; i++) {
				HRESULT hr = container[i]->OnLostDevice();
				if (FAILED(hr)) {
					return false;
				}
			}
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::Render(int index, float x, float y, float z,  float sx, float sy, float angle)
		{
			Matrix44 world;
			world.Identity();
			Matrix44::SetTransform(&world, sx,sy, 1, 0, 0,angle, x, y, z);

			fontColor.a = charInfo[index].transparency;
			container[index]->Render(world, fontColor);
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::RenderAll(float x, float y, float z,  float sx, float sy, float angle)
		{	
			float startX =x;

			for (int i=0; i < columnNum; i++) {
				for (int j=0; j< rowNum; j++) {
					size_t n = i*rowNum+j;
					if (n > textLength) {return;}
					if (n >= charInfo.size()) {
						return;
					}
					if (n > 0) {
						//一個前の文字が描画済みであるなら、次に描画する文字の透明度を少しずつ下げる
						if (charInfo[n-1].isDrawed) {
							//透明度を下げていく
							charInfo[n].transparency += transparent/textSpeed;
							if (charInfo[n].transparency >= transparent/*Nyx::Limits::UCharMax/2*/) {
								charInfo[n].transparency=transparent;/*Nyx::Limits::UCharMax/2;*/
								charInfo[n].isDrawed=true;
							}
						}
					}

					Render(n, x, y, z, sx, sy, angle);
					x += fontSize;
				}
				y += fontSize;; 
				x = startX;
			}

			/*Matrix44 world = Matrix44::Unit;
			int startX = x;
			int startY = y;
			for (int i=0, cnt=0; i < container.size(); ++i) {
			world=Matrix44::Unit;
			DXTextureFont* font = container[i];

			if (textstring[i] == '\n') {
			x = startX- font->GetWidth();
			y = startY+font->GetHeight();
			cnt = 0;
			continue;
			}else {
			x=startX + cnt*font->GetWidth();
			++cnt;
			}
			Matrix44::Transform(&world, sx, sy, 1, 0, 0, angle,  x, y, z);
			font->Render(world, Color4c::White);
			}*/
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetText(std::wstring text) {
			//textstringをクリア
			textstring = L"";
			textstring.clear();


			textstring = text;
			cursorRead = 0;
		}

		void DXTextureFontManager::SetTextLength(int len) {
			textLength = len;
		}

		int DXTextureFontManager::GetTextLength() const{
			return textLength;
		}
		//-----------------------------------------------------------------------------------------
		//
		std::wstring DXTextureFontManager::GetText() const {
			return textstring;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetFontSize(int size) {
			cursorRead = 0;
			fontSize = size;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetFontSize() const
		{
			return fontSize;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetFontColor(Color4c color) {
			fontColor = color;
		}

		//-----------------------------------------------------------------------------------------
		//
		Color4c DXTextureFontManager::GetFontColor() 
			const 
		{
			return fontColor;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::AdjustRowAndColumn(int width, int height) {

			//マージンは無視することにした
			//width -= margin * 2;//右端と左端両方なので

			columnNum = height/fontSize;
			rowNum = width/fontSize;

			SetTextLength(columnNum * rowNum);
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetRow(int n) {
			rowNum = n;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetRow() 
			const {
				return rowNum;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetColumn(int n) {
			columnNum = n;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetColumn() 
			const
		{
			return columnNum;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetSpeed(int s) {
			if (s <= 0 ) {s = 1;}
			textSpeed = s;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetSpeed() 
			const 
		{
			return textSpeed;
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFontManager::SetTransparent(int t) {
			if (t <= 0 ) {t = 1;}
			transparent = t;
		}

		//-----------------------------------------------------------------------------------------
		//
		int DXTextureFontManager::GetTransparent() 
			const 
		{
			return transparent;
		}
	}
}