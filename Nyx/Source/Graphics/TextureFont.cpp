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
#include "Graphics/TextureFont.h"
#include "detail/DX9/DirectXDefinition.h"
#include "detail/GDI/Font.h"
#include "Primitive/Rect.h"
#include "FontInfo.h"
namespace Nyx {
	struct TextureFont::PImpl
	{
		wchar_t character_;
		FontInfo fontInfo_;
		D3dXSprite9Ptr sprite_;
		D3dTexture9Ptr texture_;

		//-----------------------------------------------------------------------------------------
		//
		PImpl()
			: character_(L' '), fontInfo_(), sprite_(nullptr), texture_(nullptr){

		}

		//-----------------------------------------------------------------------------------------
		//
		PImpl(wchar_t ch, const FontInfo& fontInfo)
			: character_(ch), fontInfo_(fontInfo), sprite_(nullptr), texture_(nullptr) {
		}

		//-----------------------------------------------------------------------------------------
		//
		void Set(wchar_t ch, const FontInfo& fontInfo) {
			character_ = ch;
			fontInfo_ = fontInfo;

			LoadTexture();
		}

		//-----------------------------------------------------------------------------------------
		//
		void CreateSprite() {
			// D3dDevice9オブジェクトの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			//スプライトの作成
			LPD3DXSPRITE sprite = NULL;
			HRESULT hr = D3DXCreateSprite(d3dDevice.get(), &sprite);
			if (FAILED(hr)) {
				DebugOutput::Trace("スプライトの生成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("スプライトの生成に失敗しました。", hr);
			}

			//スマートポインタの管理下に置く
			sprite_ = D3dXSprite9Ptr(sprite, false);
		}

		//-----------------------------------------------------------------------------------------
		//
		void LoadTexture() {
			// D3dDevice9オブジェクトの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			using Nyx::GDI::Font;

			//DCの取得とフォントの生成
			HDC hdc = GetDC(NULL);
			Font font(fontInfo_.fontSize, 0, 400, false, false, false, SHIFTJIS_CHARSET, fontInfo_.fontFace.c_str());
			HFONT oldFont = (HFONT)SelectObject(hdc, font.GetFont());

			// フォントビットマップ取得
			TEXTMETRIC TM;
			GetTextMetrics(hdc, &TM);
			GLYPHMETRICS GM;
			CONST MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
			auto size = GetGlyphOutline(
				hdc, (UINT)character_,
				GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			auto ptr = std::unique_ptr<BYTE[]>(new BYTE[size]);
			GetGlyphOutline(hdc, (UINT)character_, GGO_GRAY4_BITMAP, &GM, size, ptr.get(), &Mat);

			SelectObject(hdc, oldFont);
			ReleaseDC(NULL, hdc);

			//テクスチャの生成
			LPDIRECT3DTEXTURE9 texture = NULL;
			HRESULT hr = d3dDevice->CreateTexture(
				GM.gmCellIncX, TM.tmHeight,
				1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
				&texture, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("テクスチャの生成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャの生成に失敗しました。", hr);
			}

			// テクスチャにフォントビットマップ書き込み
			{
				//テクスチャサーフェイスをロック
				D3DLOCKED_RECT LockedRect = {};
				hr = texture->LockRect(0, &LockedRect, NULL, 0);
				if (FAILED(hr)) {
					DebugOutput::Trace("テクスチャのロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
					throw COMException("テクスチャのロックに失敗しました。", hr);
				}

				//メモリをクリア
				::ZeroMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight);

				// フォント情報の書き込み
				const int startX = GM.gmptGlyphOrigin.x;
				const int startY = TM.tmAscent - GM.gmptGlyphOrigin.y;
				const int fontW = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
				const int fontH = GM.gmBlackBoxY;
				const int endY = startY + fontH;
				const int endX = startX + fontW;
				const int Level = 17;
				for (auto y = startY; y < endY; ++y) {
					for (auto x = startX; x < endX; ++x){
						DWORD alpha = (255 * ptr[x - startX + fontW * (y - startY)]) / (Level - 1);
						DWORD color = 0x00ffffff | (alpha << 24);
						::CopyMemory(
							(BYTE*)LockedRect.pBits + LockedRect.Pitch * y + 4 * x,
							&color, sizeof(DWORD));
					}
				}

				//テクスチャサーフェイスをアンロック
				hr = texture->UnlockRect(NULL);
				if (FAILED(hr)) {
					DebugOutput::Trace("テクスチャのアンロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
					throw COMException("テクスチャのアンロックに失敗しました。", hr);
				}
			}

			//スマートポインタの管理下に置く
			texture_ = D3dTexture9Ptr(texture, false);
		}

		//-----------------------------------------------------------------------------------------
		//
		void Initialize() {
			CreateSprite();
			LoadTexture();
		}


		//-----------------------------------------------------------------------------------------
		//
		void Render(const Matrix44& matrix) {
			D3DXMATRIX world;
			::CopyMemory(&world, matrix.Mat, sizeof(D3DXMATRIX));

			sprite_->SetTransform(&world);
			sprite_->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);
			{
				const auto center = D3DXVECTOR3(fontInfo_.fontSize / 2.f, fontInfo_.fontSize / 2.f, 0.f);
				sprite_->Draw(
					texture_.get(), NULL, NULL, NULL,
					D3DCOLOR_RGBA(
					fontInfo_.fontColor.r, fontInfo_.fontColor.g,
					fontInfo_.fontColor.b, fontInfo_.fontColor.a));
			}
			sprite_->End();
		}
	};


	//-----------------------------------------------------------------------------------------
	//
	TextureFont::TextureFont()
		:pimpl_(std::make_shared<PImpl>())
	{
	}


	//-----------------------------------------------------------------------------------------
	//
	TextureFont::TextureFont(wchar_t character, const FontInfo& fontInfo)
		:pimpl_(std::make_shared<PImpl>(character, fontInfo))
	{
		Initialize(character, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Set(wchar_t character, const FontInfo& fontInfo) {
		Assert(pimpl_ != nullptr);
		pimpl_->Set(character, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Initialize(wchar_t character, const FontInfo& fontInfo) {
		Assert(pimpl_ != nullptr);
		pimpl_->Set(character, fontInfo);
		pimpl_->Initialize();
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::SetFontInfo(const FontInfo& fontInfo){
		Assert(pimpl_ != nullptr);
		pimpl_->fontInfo_ = fontInfo;
	}


	//-----------------------------------------------------------------------------------------
	//
	FontInfo TextureFont::GetFontInfo() const{
		Assert(pimpl_ != nullptr);
		return pimpl_->fontInfo_;
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::SetRect(const Rect2i& rect) {
		Assert(pimpl_ != nullptr);
	}


	//-----------------------------------------------------------------------------------------
	//
	Rect2i TextureFont::GetRect() const {
		Assert(pimpl_ != nullptr);
		return Rect2i();
	}



	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::SetColor(const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->fontInfo_.fontColor = color;
	}


	//-----------------------------------------------------------------------------------------
	//
	Color4c TextureFont::GetColor() const{
		Assert(pimpl_ != nullptr);
		return pimpl_->fontInfo_.fontColor;
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Render(const Matrix44& matrix) const{
		Assert(pimpl_ != nullptr);
		pimpl_->Render(matrix);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Release() {
		Assert(pimpl_ != nullptr);
		pimpl_->sprite_->OnLostDevice();
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Recovery(){
		Assert(pimpl_ != nullptr);
		pimpl_->sprite_->OnResetDevice();
	}
}