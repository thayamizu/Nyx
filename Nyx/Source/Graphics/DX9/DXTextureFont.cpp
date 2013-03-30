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
#include "Graphics/ITextureFont.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/DXTextureFont.h"
#include "Graphics/GDI/Font.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Color4c.h"


namespace Nyx {
	namespace DX9 {
		using Nyx::GDI::Font;

		//--------------------------------------------------------------------------------
		//
		DXTextureFont::DXTextureFont():ITextureFont(1,1, false, false) 
		{
		}

		//--------------------------------------------------------------------------------
		//
		DXTextureFont::~DXTextureFont() 
		{
			Release();
		}

		//--------------------------------------------------------------------------------
		//
		void DXTextureFont::Release() 
		{
			if (sprite!=NULL) {
				SafeRelease(sprite);
			}
			if (texture!=NULL) {
				//	texture->AddRef();//つじつま合わせ
				SafeRelease(texture);
			}


		}

		//--------------------------------------------------------------------------------
		//
		void DXTextureFont::Create(DirectGraphicsDevice& device, int fontSize, wchar_t *ch, std::wstring fontName) 
		{
			HRESULT hr;

			//DCの取得とフォントの生成
			HDC hdc = GetDC(NULL);
			Font font(fontSize, 0, 500, false, false, false, SHIFTJIS_CHARSET, fontName.c_str());
			HFONT oldFont = (HFONT)SelectObject(hdc, font.GetFont());

			// フォントビットマップ取得
			uint code = (uint)*ch;
			TEXTMETRIC TM;
			GetTextMetrics( hdc, &TM );
			GLYPHMETRICS GM;
			CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};
			DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			BYTE *ptr = new BYTE[size];
			GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);


			//TEXTMETRIC TM;
			//GetTextMetrics( hdc, &TM );   
			//GLYPHMETRICS GM;
			//static const MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};
			//ulong size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			//uchar *ptr = new uchar[size];
			//GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

			SelectObject(hdc, oldFont);
			ReleaseDC(NULL, hdc);

			// テクスチャ作成
			Direct3DDevice d3dDevice = device.GetDevice();
			SetWidth( fontSize);
			SetHeight(fontSize);

			//スプライトの作成
			hr = D3DXCreateSprite(d3dDevice,&sprite);
			Assert(hr == S_OK);

			hr = d3dDevice->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
			texture->AddRef();//カウントを増やしておく
			Assert(hr == S_OK);
			if(FAILED(hr)) {
				//デバイスロスト対策
				/*	hr = d3dDevice->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
				Assert(hr == S_OK);	
				if (FAILED(hr)) {
				return;
				}*/
			}

			// テクスチャにフォントビットマップ書き込み
			D3DLOCKED_RECT LockedRect;
			hr = texture->LockRect(0, &LockedRect, NULL, 0);
			Assert(hr == S_OK);
			if(FAILED(hr)) {
				return;
			}

			// フォント情報の書き込み
			// iOfs_x, iOfs_y : 書き出し位置(左上)
			// iBmp_w, iBmp_h : フォントビットマップの幅高
			// Level : α値の段階 (GGO_GRAY8_BITMAPなので65段階)
			int iOfs_x = GM.gmptGlyphOrigin.x;
			int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
			int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;
			int iBmp_h = GM.gmBlackBoxY;
			int Level = 17;
			int x, y;
			DWORD Alpha, Color;
			FillMemory(LockedRect.pBits , LockedRect.Pitch * TM.tmHeight, 0);
			for(y=iOfs_y; y<iOfs_y+iBmp_h; y++)
				for(x=iOfs_x; x<iOfs_x+iBmp_w; x++){
					Alpha = (255 * ptr[x-iOfs_x + iBmp_w*(y-iOfs_y)]) / (Level-1);
					Color = 0x00ffffff | (Alpha<<24);
					memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4*x, &Color, sizeof(DWORD));
				}


				texture->UnlockRect(0);
				SafeDelete(ptr);


				//リソースデータをキャッシュ
				//SetResourceData(L"フォント",LockedRect.Pitch * TM.tmHeight, (uchar*)LockedRect.pBits+LockedRect.Pitch*iOfs_y + 4*iOfs_x);
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXTextureFont::OnLostDevice() {
			return sprite->OnLostDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXTextureFont::OnResetDevice() {
			return sprite->OnResetDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFont::Restore() {
			//リソースがキャッシュされていない
			if (GetResourceSize() == 0) {return;}
			////キャッシュしてあるリソースデータを読み込む
			//uchar* buffer;
			//uint size = GetResourceSize();
			//buffer = new uchar[size];
			//GetResourceData(&buffer);

			//Direct3DDevice d3dDevice;
			//HRESULT hr = sprite->GetDevice(&d3dDevice);
			//Assert(SUCCEEDED(hr));

			//hr = D3DXCreateTextureFromFileInMemory(d3dDevice, (void*)buffer, size, &texture);
			//Assert(hr == S_OK);
		}

		//--------------------------------------------------------------------------------
		//
		void DXTextureFont::Render(Matrix44& world, Color4c color) 
		{
			//描画位置決め
			RECT rect= {0,0, GetWidth(),GetHeight()};
			D3DXVECTOR3 pos(0, 0, 0);
			D3DXVECTOR3 center(GetWidth()/2.f, GetHeight()/2.f, 0);
			//ワールド行列に中心位置の分を加算
			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;

			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			sprite->Draw(texture,&rect, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}
	}
}
